# 🎮 Tic-Tac-Toe

Game Tic-Tac-Toe sederhana yang dibuat menggunakan **C++** dan **Raylib**.

Project ini dibuat sebagai project pembelajaran untuk melatih pemrograman C++, konsep Object-Oriented Programming (OOP), game logic, serta pembuatan GUI menggunakan Raylib.

## 📸 Fitur

- 🧑 Pemain melawan Bot
- ❌ Pemain menggunakan `X`
- ⭕ Bot menggunakan `O`
- 🎲 Bot memilih langkah secara acak
- ⏱️ Bot memiliki jeda berpikir 500 ms
- 🏆 Deteksi kemenangan
- 🤝 Deteksi permainan seri
- 🔄 Tombol bermain kembali
- 🚪 Tombol keluar
- 🖥️ Antarmuka grafis menggunakan Raylib
- ✨ X dan O dibuat lebih besar dan tebal

## 🛠️ Teknologi

- **C++**
- **Raylib**
- **MSYS2 UCRT64**
- **MinGW-w64**
- **Git / GitHub**

## 📂 Struktur Project

```text
tictactoe/
├── gui_test.cpp
├── bot.h
├── bot.cpp
└── README.md
```

### Penjelasan File

| File | Fungsi |
|------|--------|
| `gui_test.cpp` | Program utama, GUI, input pemain, game state, dan logika permainan |
| `bot.h` | Deklarasi class `Bot` |
| `bot.cpp` | Logika pergerakan Bot |
| `README.md` | Dokumentasi project |

## 🎮 Cara Bermain

1. Jalankan game.
2. Klik salah satu kotak kosong untuk menempatkan `X`.
3. Bot akan menempatkan `O` setelah beberapa saat.
4. Buat tiga simbol yang sama secara horizontal, vertikal, atau diagonal untuk menang.
5. Jika semua kotak terisi tanpa ada pemenang, permainan berakhir seri.
6. Setelah permainan selesai:
   - Klik **YES** untuk bermain kembali.
   - Klik **EXIT** untuk keluar.

## 🧠 Logika Permainan

Game menggunakan sistem **Game State** untuk menentukan giliran pemain.

```text
PLAYER_TURN
     │
     ▼
Pemain menempatkan X
     │
     ├── Pemain menang ──────► GAME_OVER
     │
     ├── Board penuh ────────► GAME_OVER
     │
     ▼
BOT_TURN
     │
     ▼
Bot menempatkan O
     │
     ├── Bot menang ─────────► GAME_OVER
     │
     ├── Board penuh ────────► GAME_OVER
     │
     ▼
PLAYER_TURN
```

## 🤖 Bot

Saat ini Bot menggunakan strategi sederhana berupa **pemilihan posisi secara acak**.

Bot terlebih dahulu mencari seluruh kotak yang masih kosong:

```cpp
if (board[row][col] == ' ') {
    emptyRows[count] = row;
    emptyCols[count] = col;
    count++;
}
```

Kemudian Bot memilih salah satu kotak kosong secara acak:

```cpp
int choice = rand() % count;
```

Setelah itu Bot menempatkan `O` pada posisi tersebut.

### Tingkat Kesulitan Bot

Bot saat ini masih menggunakan algoritma sederhana dan belum memiliki strategi khusus seperti:

- Memblokir kemenangan pemain
- Memprioritaskan bagian tengah
- Memprioritaskan sudut
- Minimax
- Game-tree search

Strategi tersebut dapat ditambahkan pada versi berikutnya.

## ⏱️ Jeda Bot

Bot memiliki jeda sekitar **500 milidetik** sebelum melakukan langkah.

```cpp
const float BOT_DELAY = 0.5f;
```

Jeda dibuat menggunakan `GetFrameTime()` sehingga tidak menghentikan game loop.

Dengan cara ini game tetap dapat melakukan rendering dengan normal selama Bot "berpikir".

## 🖥️ Instalasi

### 1. Install MSYS2

Install MSYS2 kemudian gunakan terminal **UCRT64**.

### 2. Install Raylib

Jalankan:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

### 3. Clone Repository

```bash
git clone <url-repository-kamu>
```

Masuk ke folder project:

```bash
cd tictactoe
```

## 🔨 Compile

Gunakan command berikut:

```bash
g++ gui_test.cpp bot.cpp -o tictactoe_gui.exe -lraylib
```

Jika proses compile berhasil, jalankan:

```bash
./tictactoe_gui.exe
```

## 💻 Environment

Project ini dikembangkan menggunakan:

```text
Bahasa          : C++
Graphics        : Raylib
Compiler        : MinGW-w64
Environment     : MSYS2 UCRT64
Sistem Operasi  : Windows
```

## 📚 Hal yang Dipelajari

Melalui project ini, saya mempraktikkan:

- Class dan Object pada C++
- Object-Oriented Programming (OOP)
- Pemisahan file `.h` dan `.cpp`
- Function
- Array
- Array 2 dimensi
- Perulangan
- Percabangan
- Game State
- Game Logic
- Input menggunakan mouse
- Random number generation
- GUI programming
- Penggunaan library Raylib
- Kompilasi C++ menggunakan library eksternal
- Penggunaan MSYS2
- Pemisahan logic Bot dari program utama

## 🚀 Pengembangan Selanjutnya

Beberapa fitur yang ingin dikembangkan:

- [ ] Bot yang lebih pintar
- [ ] Tingkat kesulitan Easy / Medium / Hard
- [ ] Algoritma Minimax
- [ ] Sistem skor
- [ ] Animasi garis kemenangan
- [ ] Efek hover pada kotak
- [ ] Efek suara
- [ ] Background music
- [ ] UI yang lebih menarik
- [ ] Main menu
- [ ] Input nama pemain
- [ ] Memisahkan game logic menjadi beberapa class
- [ ] Menambahkan unit test
