# Prometheus

An encrypted, next-generation filesystem that aims to protect from cryptoanalysis as well as 5$ wrench attacks.

Not licensed AGPLv3 yet as the project is still ongoing. Once the project reaches a stable base, we'll change the license.

**Overview**

- Features and Comparison
- Roadmap and ETA
  - Roadmap
- [Structures](#Structures)
- [Footnotes](#Footnotes)

## Features and Comparison

_Veracrypt is not a filesystem_

**Prometheus is unlike other filesystems based on publicy available research documents and tries to implement the measurements suggested in those.**

- Post-quantum secure encryption
- Invisible plausible deniability[^1]
- Cascade encryption
- Lightweight kernel module (few hundred lines) for increased performance
- Supports multiple volumes as well as decoy volumes
- Supports multiple users with a shared folder
- Proper ACL implementation

## Roadmap and ETA

A working build integrating all features initially planned is estimated to be released 2029.

### Roadmap

| Description | ETA or date of completion | Completed |
| --- | --- | --- |
| Brainstorming | 01.05.2026 | ❌ |
| Language Selection | 07.05.2026 | ❌ |
| Development | - | ❌ |

## Structures

This section helps organizing all issues relevant for development.

| Structure | Issue | Description |
| --- | --- | --- |
| File Header | [#10](https://github.com/kegomimu/prometheus/issues/10) | Stores file properties and chunk addresses |
| Directory Header | [#14](https://github.com/kegomimu/prometheus/issues/14) | Includes the corresponding files |
| Keyslot | [#17](https://github.com/kegomimu/prometheus/issues/17) | Contains encryption secrets |
| User Header | [#16](https://github.com/kegomimu/prometheus/issues/16) | Allows exchange of files between multiple users while preserving security for the private keys |

## Footnotes

[^1]: Based on INVISILINE