# Nusacoin Core 0.26.60

Nusacoin Core is the reference software for the Nusacoin (NUX) peer-to-peer
digital currency network.

## Programs in this package

| Program         | What it is for                                           |
|-----------------|----------------------------------------------------------|
| nusacoin-qt     | Graphical wallet — double-click to start (recommended)   |
| nusacoind       | The node/daemon, runs in the background (no window)      |
| nusacoin-cli    | Command-line tool for talking to a running nusacoind     |
| nusacoin-tx     | Utility for creating and inspecting raw transactions     |
| nusacoin-wallet | Wallet maintenance tool (run only while the node is off) |

## Quick start

1. Start `nusacoin-qt` (on Windows you can also use the installer).
2. The first launch downloads the Nusacoin blockchain. This can take a long
   time — leave the program running until it finishes synchronizing.
3. Your wallet lives in the data directory (see below). **Back it up
   regularly**: in nusacoin-qt, use File → Backup Wallet and store the copy
   somewhere safe. Anyone holding your wallet file can spend your coins.

## Data directory

- Windows: `%APPDATA%\Nusacoin`
- macOS: `~/Library/Application Support/Nusacoin`
- Linux: `~/.nusacoin`

## Notes

- These are unsigned community builds. Windows SmartScreen or macOS
  Gatekeeper may warn on first launch — this is expected.
- Never share your wallet file or private keys with anyone.

## Getting help

https://github.com/TaobotX11/nusacoin/issues
