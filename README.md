# Prometheus

[![Open Source Helpers](https://www.codetriage.com/kegomimu/prometheus/badges/users.svg)](https://www.codetriage.com/kegomimu/prometheus)

An encrypted, next-generation filesystem that aims to protect from cryptoanalysis as well as 5$ wrench attacks.

Not licensed AGPLv3 yet as the project is still ongoing. Once the project reaches a stable base, we'll change the license.

**Overview**

- Features
  - Research papers
- Roadmap and ETA
  - Roadmap
- Structures
- Footnotes

## Features

_First off: Veracrypt is not a filesystem_

**Prometheus is unlike other filesystems based on publicy available research documents and tries to implement the measurements suggested in those.**

- Post-quantum secure encryption
- Invisible plausible deniability[^1]
- Cascade encryption
- Lightweight kernel module (few hundred lines) for increased performance
- Supports multiple volumes as well as decoy volumes
- Supports multiple users with a shared folder
- Proper ACL implementation

### Research papers

These papers are actively being used to maximize security.

_All papers were retrieved on the 12th February, 2026_

- [Extension Framework for File Systems in User space](https://www.usenix.org/system/files/atc19-bijlani.pdf)
- [The missing guide to the security of filesystems and file APIs](https://gergelykalman.com/slides/the_missing_guide_to_filesystem_security_v1.pdf)
- [TOCTTOU Vulnerabilities in UNIX-Style File Systems: An Anatomical Study](https://www.usenix.org/legacy/events/fast05/tech/full_papers/wei/wei.pdf)
- [Modeling and Preventing TOCTTOU Vulnerabilities in Unix-Style File Systems](https://users.cis.fiu.edu/~weijp/Jinpeng_Homepage_files/toctou_journal_elsevier.pdf)
- [File Hijacking Vulnerability: The Elephant in the Room](https://www.ndss-symposium.org/wp-content/uploads/2024-38-paper.pdf)
- [Operation Systems: File Systems](https://course.ccs.neu.edu/cs3650f21/new/Lectures/12/lecture_16--File_systems.pdf)
- [A Study of Linux File System Evolution](https://research.cs.wisc.edu/adsl/Publications/fsstudy-fast13.pdf)
- [Understanding Security Vulnerabilities in File Systems](https://jianh.web.engr.illinois.edu/papers/securefs-apsys19.pdf)
- [File Systems as Processes](https://www.usenix.org/system/files/hotstorage19-paper-liu_0.pdf)
- [Plausibly deniable encryption with large language models](https://openreview.net/pdf?id=7suavRDxe8)
- [Artifice: A Deniable Steganographic File System](https://www.usenix.org/system/files/foci19-paper_barker.pdf)
- [INVISILINE: Invisible Plausibly-Deniable Storage](https://users.cs.fiu.edu/~carbunar/invisiline.pdf)
- [Enabling Plausible Deniability in Flash-based Storage through Data Permutation](https://weidong-zhu.github.io/files/mute_acsac25.pdf)
- [Threat Models for Analyzing Plausible Deniability of Deniable File Systems](https://www.riverpublishers.com/journal/journal_articles/RP_Journal_2445-9739_20171012.pdf)
- [Data corruption in plausibly deniable storage: challenges and potential solutions](https://infoscience.epfl.ch/server/api/core/bitstreams/d19851b2-9a7b-4dc8-bb83-e32dcc937b1c/content)
- [Apple File System Reference](https://developer.apple.com/support/downloads/Apple-File-System-Reference.pdf)
- [Technical White Paper for Copy Anti-tampering](https://e.huawei.com/marketingcloud/pep/asset/20000001/Material/d3dc434846db428082a1ad0f1f7eaff4/M2T1A590N971850264796590242/Huawei%20OceanProtect%20%20Appliance%201_6_0%20Technical%20White%20Paper%20for%20Copy%20Anti-tampering.pdf)
- [LUKS2 On-Disk Format Specification](https://fossies.org/linux/cryptsetup/docs/on-disk-format-luks2.pdf)
- [What users should know about Full Disk Encryption based on LUKS](https://eprint.iacr.org/2016/274.pdf)
- [Filesystem Security](https://cs.brown.edu/cgc/net.secbook/se01/handouts/Ch03-FilesystemSecurity.pdf)
- [Modernizing File System through In-Storage Indexing](https://www.usenix.org/system/files/osdi21-koo.pdf)
- [Persistence: File Systems and RAID](https://tddg.github.io/cs571-spring21/public/lecs/lec10-persis-fs-raid+note.pdf)
- [I know What You Sync: Covert and Side Channel Attacks on File Systems via syncfs](https://arxiv.org/pdf/2411.10883v1)

## Roadmap and ETA

A working build integrating all features initially planned is estimated to be released 2029.

### Roadmap

| Description | ETA or date of completion | Completed |
| --- | --- | --- |
| Brainstorming | 01.07.2026 | ❌ |
| Language Selection | 07.07.2026 | ❌ |
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