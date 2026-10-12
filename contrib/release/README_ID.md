# Nusacoin Core 0.26.60

Nusacoin Core adalah perangkat lunak resmi jaringan mata uang digital
peer-to-peer Nusacoin (NUX).

## Program di dalam paket ini

| Program         | Fungsinya                                                    |
|-----------------|--------------------------------------------------------------|
| nusacoin-qt     | Dompet grafis — klik dua kali untuk menjalankan (disarankan) |
| nusacoind       | Node/daemon yang berjalan di latar belakang (tanpa jendela)  |
| nusacoin-cli    | Perkakas baris perintah untuk berkomunikasi dengan nusacoind |
| nusacoin-tx     | Perkakas untuk membuat dan memeriksa transaksi mentah        |
| nusacoin-wallet | Perkakas perawatan dompet (jalankan hanya saat node mati)    |

## Mulai cepat

1. Jalankan `nusacoin-qt` (di Windows bisa juga lewat installer).
2. Saat pertama dijalankan, program mengunduh blockchain Nusacoin. Proses ini
   bisa memakan waktu lama — biarkan program tetap berjalan sampai
   sinkronisasi selesai.
3. Dompet Anda tersimpan di direktori data (lihat bawah). **Cadangkan secara
   berkala**: di nusacoin-qt pilih File → Backup Wallet, dan simpan salinannya
   di tempat yang aman. Siapa pun yang memegang file dompet Anda bisa
   membelanjakan koin Anda.

## Direktori data

- Windows: `%APPDATA%\Nusacoin`
- macOS: `~/Library/Application Support/Nusacoin`
- Linux: `~/.nusacoin`

## Catatan

- Ini adalah build komunitas tanpa tanda tangan digital. Windows SmartScreen
  atau macOS Gatekeeper mungkin memberi peringatan saat pertama dibuka —
  hal ini wajar.
- Jangan pernah membagikan file dompet atau private key Anda kepada siapa pun.

## Bantuan

https://github.com/TaobotX11/nusacoin/issues
