# prometheus

An encrypted, next-generation filesystem that aims to protect from cryptoanalysis as well as 5$ wrench attacks.

Not licensed GPLv2 yet as the project is still ongoing. Once the project reaches a stable base, we'll change the license.

## Roadmap and ETA

The final release is estimated to be released 2029.

### Roadmap

| Description | ETA or date of completion | Completed |
| --- | --- | --- | --- |
| Brainstorming | 01.06.2026 | ❌ |
| Language Selection | - | ❌ |
| Development | - | ❌ |

## Structures

This section helps organizing all issues relevant for development.

| Structure | Issue | Description |
| --- | --- |
| File Header | - | Stores file properties and chunk addresses |
| Directory Header | [#14](https://github.com/kegomimu/prometheus/issues/14) | Includes the corresponding files |
| User Header | [#16](https://github.com/kegomimu/prometheus/issues/16) | Allows exchange of files between multiple users while preserving security for the private keys |

## Threat Model

The threat model does not include migitations for the attacks below as those can't be migitated on a software level
- Evil maid attacks
- Social engineering

### Overview

- [Assets](#Assets)
- [Adversaries](#Adversaries)
- [Capabilities](#Capabilities)
- [Assumptions](#Assumptions)
- [Scenarios](#Scenarios)

### Assets

- Primary data: sensitive files, cryptocurrency wallets, private keys stored on the device.
- Decoy data: files and account(s) presented to an adversary under coercion.
- Device state: operating system, running processes, filesystem integrity.
- Authentication credentials: passwords, passphrases, keys for primary and decoy accounts.

### Adversaries

- Low-skill opportunist: gains casual access to an unlocked device or guesses weak credentials.
- Sophisticated attacker: skilled in cryptanalysis, forensic tools, or OS compromise; may perform hardware or software-based forensic analysis.
- Coercive attacker: uses physical force, threats, or legal compulsion to obtain credentials and force access.
- Insider or informed adversary: knows or strongly suspects the existence of particular sensitive assets (e.g., a Bitcoin wallet) and will not be satisfied with a plausible decoy.

### Capabilities

- Physical access to the device (before, during, or after boot).
- Ability to compel the user to reveal credentials.
- Tools to perform forensic analysis, brute-force/offline attacks, or memory extraction.
- Knowledge of user's online footprints (e.g., social media)

### Assumptions

- User can choose and implement strong, well-vetted cryptographic algorithms and key management.
- User can create and maintain a convincing decoy account and decoy data.
- Attacker may be able to inspect device state and boot environment.
- Attacker may coerce the user while the device is powered off, powered on, or running.

### Scenarios

1. Opportunistic access to unlocked device
    - Risk: Attacker accesses primary data directly.
    - Mitigation: Lock screen when unattended; full-disk encryption (FDE) with strong passphrase; short auto-lock.

2. Offline forensic analysis after seizure (device powered off)
    - Risk: Attacker performs cold-boot attacks, chip-off, or mounts storage to access data.
    - Mitigation: FDE with strong, up-to-date algorithms; hardware-backed encryption (TPM/secure enclave) where appropriate; cryptographic key protections; wipe keys from RAM on shutdown; use disk-level secure erase when required.

3. Memory or runtime extraction while device is on
    - Risk: Credentials, keys, or active wallet data exposed in RAM or swap.
    - Mitigation: Avoid leaving device unattended while unlocked; hibernate/lock when not in use; disable or encrypt swap; use hardware wallets for cryptocurrency private keys (keep them off host RAM).

4. Coercion to reveal credentials
    - Risk: User forced to reveal passphrase to primary account.
    - Mitigation: Maintain a convincing decoy account with realistic data and access limits; use separate passphrases for decoy and primary; plausible behavior and documentation supporting decoy ownership.

5. Attacker who knows about the sensitive asset
    - Risk: If adversary knows a wallet or asset exists, a decoy is unlikely to satisfy them; coercion may escalate to violence.
    - Mitigation: Recognize limits — if attacker is convinced the asset exists, technical measures and decoys may not prevent coercion. Prioritize personal safety; consider risk reduction strategies (minimizing visible evidence of asset ownership, using cold storage, splitting keys geographically).

6. OS or hardware compromise prior to boot
    - Risk: Bootkit/rootkit or hardware tampering undermines all protections and can capture credentials or present false decoys.
    - Mitigation: Verify integrity of boot environment (secure boot, measured boot, verified boot); check hardware seals/BIOS firmware; use live-boot from trusted media when required; keep an offline, audited recovery environment.

7. Identifier leakage via online presence
    - Risk: Public screenshots or posts reveal usernames, display names, or other identifiers that link a person to a primary account, undermining decoy plausibility.
    - Mitigation: Avoid posting identifiable info tied to primary accounts; ensure decoy account metadata is consistent with claimed identity when used.