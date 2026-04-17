// Metadata header

#[repr(C)]
pub struct Metadata {
    pub id: [u8; 16], // UUID
    pub key_len: u16, // Length of key in byte
    pub val_len: u32, // Length of value in bytes
    pub flags: u8,           // bit0 = val_inline, bit1 = key_inline
    pub _pad: u8,            // padding to align offsets
    pub key_offset: u64,     // blob file offset if key not inline (0 = inline)
    pub val_offset: u64,     // blob file offset if value not inline (0 = inline)
    pub inline_key: [u8; 32],   // small-key inline storage (valid if key_inline)
    pub inline_val: [u8; 128],  // small-value inline storage (valid if val_inline)
}

#[repr(C)]
pub struct BlobRecordHeader {
    pub length: u32,         // length of the blob data
    pub _pad: [u8; 4],       // pad to 8-byte alignment if desired
}
// After this struct, raw bytes follow (with the specified length)