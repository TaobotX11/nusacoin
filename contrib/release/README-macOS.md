# Nusacoin Core for macOS

Nusacoin Core is the reference software for the Nusacoin (NUX) peer-to-peer
digital currency network.

This is a universal build: one app that runs natively on both Intel (x86_64)
and Apple Silicon (ARM64) Macs, on macOS 11.0 or later.

## Installing

1. Copy `Nusacoin-Qt.app` from this disk image into your Applications folder.
2. Eject the disk image.

## First launch (unsigned app)

This build is not signed with an Apple Developer certificate, so macOS
Gatekeeper will warn you on first launch. This is expected.

1. In Finder, open Applications, right-click (or Control-click)
   `Nusacoin-Qt` and choose **Open**.
2. Click **Open** in the confirmation dialog. On recent macOS versions you may
   instead need System Settings → Privacy & Security → **Open Anyway**.

You only need to do this once.

## Quick start

1. Start Nusacoin-Qt from Applications.
2. The first launch downloads the Nusacoin blockchain. This can take a long
   time — leave the program running until it finishes synchronizing.
3. **Back up your wallet regularly**: use File → Backup Wallet and store the
   copy somewhere safe. Anyone holding your wallet file can spend your coins.

## Data directory

`~/Library/Application Support/Nusacoin`

## Notes

- Wallet files are not freely interchangeable between Intel and Apple Silicon
  Macs: a wallet created or upgraded on Apple Silicon may not open on Intel.
  Back up `wallet.dat` before moving a wallet between machines.
- Never share your wallet file or private keys with anyone.

## Getting help

https://github.com/TaobotX11/nusacoin/issues
