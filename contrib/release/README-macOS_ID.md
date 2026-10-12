# Nusacoin Core untuk macOS

Nusacoin Core adalah perangkat lunak referensi untuk jaringan mata uang
digital peer-to-peer Nusacoin (NUX).

Ini adalah build universal: satu aplikasi yang berjalan native di Mac Intel
(x86_64) maupun Apple Silicon (ARM64), pada macOS 11.0 atau lebih baru.

## Cara install

1. Salin `Nusacoin-Qt.app` dari disk image ini ke folder Applications.
2. Eject disk image.

## Peluncuran pertama (aplikasi unsigned)

Build ini tidak ditandatangani dengan sertifikat Apple Developer, sehingga
Gatekeeper macOS akan memberi peringatan saat pertama dibuka. Ini normal.

1. Di Finder, buka Applications, klik kanan (atau Control-klik)
   `Nusacoin-Qt` lalu pilih **Open**.
2. Klik **Open** di dialog konfirmasi. Pada macOS versi baru, Anda mungkin
   perlu membuka System Settings → Privacy & Security → **Open Anyway**.

Langkah ini hanya perlu dilakukan sekali.

## Mulai cepat

1. Jalankan Nusacoin-Qt dari Applications.
2. Peluncuran pertama mengunduh blockchain Nusacoin. Proses ini bisa memakan
   waktu lama — biarkan program berjalan sampai sinkronisasi selesai.
3. **Cadangkan wallet Anda secara rutin**: gunakan File → Backup Wallet dan
   simpan salinannya di tempat aman. Siapa pun yang memegang file wallet Anda
   bisa membelanjakan koin Anda.

## Direktori data

`~/Library/Application Support/Nusacoin`

## Catatan

- File wallet tidak bisa bebas dipertukarkan antara Mac Intel dan Apple
  Silicon: wallet yang dibuat atau di-upgrade di Apple Silicon mungkin tidak
  bisa dibuka di Intel. Cadangkan `wallet.dat` sebelum memindahkan wallet
  antar mesin.
- Jangan pernah membagikan file wallet atau private key Anda kepada siapa pun.

## Bantuan

https://github.com/TaobotX11/nusacoin/issues
