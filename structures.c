#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdatomic.h>

#define FS_MAGIC 0x4D585346UL
#define SUPERBLOCK_VERSION 1
#define UUID_LEN 16
#define SALT_LEN 32
#define HASH_LEN 32
#define SIG_LEN 64
#define PAD_NAME_LEN 256
#define RESERVED_LEN 160

typedef struct __attribute__((packed, aligned(8))) filesystem {
    uint32_t magic;
    uint16_t version;
    uint16_t header_len;
    uint64_t seqno;
    uint64_t epoch;
    uint8_t  fs_uuid[UUID_LEN];
    uint8_t  label[PAD_NAME_LEN];
    uint8_t  root_merkle[HASH_LEN];
    uint8_t  prev_root_merkle[HASH_LEN];
    uint8_t  checkpoint_hash[HASH_LEN];
    uint8_t  master_salt[SALT_LEN];
    uint8_t  meta_salt[SALT_LEN];
    uint8_t  file_salt[SALT_LEN];
    uint8_t  aead_algo;
    uint8_t  kdf_algo;
    uint8_t  hash_algo;
    uint8_t  sig_algo;
    uint8_t  reserved_algo[4];
    uint32_t block_size;
    uint64_t total_blocks;
    uint64_t payload_size_bytes;
    uint32_t max_filename_len;
    uint32_t argon2_time_cost;
    uint32_t argon2_mem_cost_kib;
    uint32_t argon2_threads;
    uint8_t  pw_hash_salt[SALT_LEN];
    uint64_t last_mount_time;
    uint8_t  reserved_ts[24];
    uint8_t  copy_id[16];
    uint8_t  copy_hash[HASH_LEN];
    uint8_t  signer_pubkey[32];
    uint8_t  sig[SIG_LEN];
    uint8_t  reserved[RESERVED_LEN];
} filesystem;

_Static_assert(sizeof(fs_superblock_t) % 8 == 0, "Superblock size must be 8-byte aligned");
_Static_assert(sizeof(fs_superblock_t) <= 4096, "Superblock must be <= 4096 bytes");

static inline void put_u16_le(uint8_t *p, uint16_t v) { p[0]=v; p[1]=v>>8; }
static inline void put_u32_le(uint8_t *p, uint32_t v) { p[0]=v; p[1]=v>>8; p[2]=v>>16; p[3]=v>>24; }
static inline void put_u64_le(uint8_t *p, uint64_t v) {
    for (int i=0;i<8;i++) p[i]=(v>>(8*i))&0xFF;
}
static inline uint16_t get_u16_le(const uint8_t *p) { return (uint16_t)p[0]|((uint16_t)p[1]<<8); }
static inline uint32_t get_u32_le(const uint8_t *p) { return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24); }
static inline uint64_t get_u64_le(const uint8_t *p) {
    uint64_t v=0;
    for(int i=0;i<8;i++) v |= (uint64_t)p[i] << (8*i);
    return v;
}

void superblock_serialize(const fs_superblock_t *sb, uint8_t *out) {
    memset(out, 0, sizeof(fs_superblock_t));

    uint8_t *p = out;
    put_u32_le(p, sb->magic); p+=4;
    put_u16_le(p, sb->version); p+=2;
    put_u16_le(p, sb->header_len); p+=2;
    put_u64_le(p, sb->seqno); p+=8;
    put_u64_le(p, sb->epoch); p+=8;
    memcpy(p, sb->fs_uuid, UUID_LEN); p+=UUID_LEN;
    memcpy(p, sb->label, PAD_NAME_LEN); p+=PAD_NAME_LEN;
    memcpy(p, sb->root_merkle, HASH_LEN); p+=HASH_LEN;
    memcpy(p, sb->prev_root_merkle, HASH_LEN); p+=HASH_LEN;
    memcpy(p, sb->checkpoint_hash, HASH_LEN); p+=HASH_LEN;
    memcpy(p, sb->master_salt, SALT_LEN); p+=SALT_LEN;
    memcpy(p, sb->meta_salt, SALT_LEN); p+=SALT_LEN;
    memcpy(p, sb->file_salt, SALT_LEN); p+=SALT_LEN;
    *p++ = sb->aead_algo; *p++ = sb->kdf_algo; *p++ = sb->hash_algo; *p++ = sb->sig_algo;
    memcpy(p, sb->reserved_algo, 4); p+=4;
    put_u32_le(p, sb->block_size); p+=4;
    put_u64_le(p, sb->total_blocks); p+=8;
    put_u64_le(p, sb->payload_size_bytes); p+=8;
    put_u32_le(p, sb->max_filename_len); p+=4;
    put_u32_le(p, sb->argon2_time_cost); p+=4;
    put_u32_le(p, sb->argon2_mem_cost_kib); p+=4;
    put_u32_le(p, sb->argon2_threads); p+=4;
    memcpy(p, sb->pw_hash_salt, SALT_LEN); p+=SALT_LEN;
    put_u64_le(p, sb->last_mount_time); p+=8;
    memcpy(p, sb->reserved_ts, 24); p+=24;
    memcpy(p, sb->copy_id, 16); p+=16;
    memcpy(p, sb->copy_hash, HASH_LEN); p+=HASH_LEN;
    memcpy(p, sb->signer_pubkey, 32); p+=32;
    memcpy(p, sb->sig, SIG_LEN); p+=SIG_LEN;
    memcpy(p, sb->reserved, RESERVED_LEN); p+=RESERVED_LEN;

    assert((size_t)(p - out) == sizeof(fs_superblock_t));
}

int superblock_deserialize(const uint8_t *in, fs_superblock_t *sb) {
    const uint8_t *p = in;
    uint32_t magic = get_u32_le(p); p+=4;
    if (magic != FS_MAGIC) return -1;
    sb->magic = magic;
    sb->version = get_u16_le(p); p+=2;
    if (sb->version != SUPERBLOCK_VERSION) return -1;
    sb->header_len = get_u16_le(p); p+=2;
    sb->seqno = get_u64_le(p); p+=8;
    sb->epoch = get_u64_le(p); p+=8;
    memcpy(sb->fs_uuid, p, UUID_LEN); p+=UUID_LEN;
    memcpy(sb->label, p, PAD_NAME_LEN); p+=PAD_NAME_LEN;
    memcpy(sb->root_merkle, p, HASH_LEN); p+=HASH_LEN;
    memcpy(sb->prev_root_merkle, p, HASH_LEN); p+=HASH_LEN;
    memcpy(sb->checkpoint_hash, p, HASH_LEN); p+=HASH_LEN;
    memcpy(sb->master_salt, p, SALT_LEN); p+=SALT_LEN;
    memcpy(sb->meta_salt, p, SALT_LEN); p+=SALT_LEN;
    memcpy(sb->file_salt, p, SALT_LEN); p+=SALT_LEN;
    sb->aead_algo = *p++; sb->kdf_algo = *p++; sb->hash_algo = *p++; sb->sig_algo = *p++;
    memcpy(sb->reserved_algo, p, 4); p+=4;
    sb->block_size = get_u32_le(p); p+=4;
    sb->total_blocks = get_u64_le(p); p+=8;
    sb->payload_size_bytes = get_u64_le(p); p+=8;
    sb->max_filename_len = get_u32_le(p); p+=4;
    sb->argon2_time_cost = get_u32_le(p); p+=4;
    sb->argon2_mem_cost_kib = get_u32_le(p); p+=4;
    sb->argon2_threads = get_u32_le(p); p+=4;
    memcpy(sb->pw_hash_salt, p, SALT_LEN); p+=SALT_LEN;
    sb->last_mount_time = get_u64_le(p); p+=8;
    memcpy(sb->reserved_ts, p, 24); p+=24;
    memcpy(sb->copy_id, p, 16); p+=16;
    memcpy(sb->copy_hash, p, HASH_LEN); p+=HASH_LEN;
    memcpy(sb->signer_pubkey, p, 32); p+=32;
    memcpy(sb->sig, p, SIG_LEN); p+=SIG_LEN;
    memcpy(sb->reserved, p, RESERVED_LEN); p+=RESERVED_LEN;

    if ((size_t)(p - in) != sizeof(fs_superblock_t)) return -1;

    // Additional data checks
    if (sb->header_len != sizeof(fs_superblock_t)) return -1;
    if (sb->block_size == 0 || sb->block_size & 0xFFF) return -1; // require multiple of 4096

    return 0;
}

void secure_zero(void *p, size_t n) {
    volatile uint8_t *vp = (volatile uint8_t *)p;
    while (n--) *vp++ = 0;
}
