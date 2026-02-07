# prometheus

An encrypted, next-generation filesystem that aims to protect from cryptoanalysis as well as 5$ wrench attacks.

Currently not licensed GPLv2 as it should not be released yet.

## Threat Model

Adversary: FBI
- Cryptoanalysis
    - Description: The adversary
- this should protect your data from cryptoanalisis based attacks if you chose good or obscure encryption algorythm.
- this won't protect your data from evil made attacks if you don't check the integrity of your OS/PC before booting. nor when leaving your PC on with no watch.
- this should protect your data in case someone forced you to give up login credentials in case you already set up a decoy user.
- however, in case the threat actor knows well you do have specific data on your PC (like a bitcoin wallet) there is no way to get away with both those data and your skin.
- also, be smart when using your PC. if you post screenshots online showing your main user's display name and then you get captured and you give the decoy user that have different display name you may become suspicious.