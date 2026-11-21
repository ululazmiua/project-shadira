#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "auth.h"
#include "buku.h"
#include "algoritma/pembanding.h"

#define PER_HALAMAN 20

static const char *NAMA_ALGORITMA[] = {"", "Bubble Sort"};
static const char *NAMA_KRITERIA[] = {"", "ID Buku", "Judul", "Tahun Terbit", "Jumlah Halaman", "Stok"};


// input
static void bacaBaris(const char *label, char *hasil, int ukuran)
{
    int panjang;

    printf("%s", label);
    if (fgets(hasil, ukuran, stdin) == NULL)
    {
        /* input habis, keluar dengan rapi */
        printf("\n");
        bebaskanSemuaData();
        exit(0); // menghentikan program secara normal
    }

    panjang = strlen(hasil); // menghitung panjang string/teks
    // Mengganti karakter Enter dengan karakter akhir string.
    if (panjang > 0 && hasil[panjang - 1] == '\n')
    {
        hasil[panjang - 1] = '\0';
    }
}

// baca inputan yang wajib, dimana jika tidak diisi itu bakalan muncul teks peringatan tigak boleh kosong
static void bacaTeksWajib(const char *label, char *hasil, int ukuran)
{
    do
    {
        bacaBaris(label, hasil, ukuran);
        if (hasil[0] == '\0')
        {
            printf("Tidak boleh kosong.\n");
        }
    } while (hasil[0] == '\0');
}

/* untuk isian yang tidak boleh kosong dan tidak boleh ada spasi (ID, url, dll) */
static void bacaTanpaSpasi(const char *label, char *hasil, int ukuran)
{
    do
    {
        bacaTeksWajib(label, hasil, ukuran);
        if (strchr(hasil, ' ') != NULL) // digunakan untuk mengecek apakah ada spasi
        {
            printf("Tidak boleh mengandung spasi.\n");
            hasil[0] = '\0';
        }
    } while (hasil[0] == '\0');
}

static int bacaAngka(const char *label, int min, int max)
{
    char teks[32];
    char *akhir;
    long nilai;

    while (1)
    {
        bacaBaris(label, teks, sizeof(teks));
        nilai = strtol(teks, &akhir, 10); // mengubah string menjadi bilangan bulat bertipe long.
        if (teks[0] != '\0' && *akhir == '\0' && nilai >= min && nilai <= max)
        {
            return (int)nilai;
        }
        printf("Input tidak valid, masukkan angka %d sampai %d.\n", min, max);
    }
}

/* tanda petik dua dipakai sebagai pemisah di file, jadi diganti */
static void gantiPetik(char *teks)
{
    int i;

    for (i = 0; teks[i] != '\0'; i++)
    {
        if (teks[i] == '"')
        {
            teks[i] = '\'';
        }
    }
}

// login, mengembalikan pointer ke user yang berhasil login
User *menuLogin(void)
{
    char username[32], password[32];
    User *user;
    int pilihan;

    printf("\n=== SISTEM PERPUSTAKAAN ===\n");
    printf("1. Login\n");
    printf("0. Keluar\n");
    pilihan = bacaAngka("Pilihan: ", 0, 1);
    if (pilihan == 0)
    {
        return NULL;
    }

    /* ulangi terus sampai username dan password benar */
    while (1)
    {
        bacaBaris("Username: ", username, sizeof(username));
        bacaBaris("Password: ", password, sizeof(password));
        user = login(username, password);
        if (user != NULL)
        {
            // kalau ada
            return user;
        }
        // kalau gak ada
        printf("Username atau password salah, coba lagi.\n");
    }
}

/*katalog */
static void pilihPengurutan(int *kriteria, int *arah, int *algoritma)
{
    *algoritma = 1; // Selalu menggunakan Bubble Sort

    printf("\nUrutkan berdasarkan:\n");
    printf("1. ID Buku\n2. Judul\n3. Tahun Terbit\n4. Jumlah Halaman\n5. Stok\n");
    *kriteria = bacaAngka("Pilih kriteria: ", 1, 5);

    printf("\n1. Naik (A-Z / terlama / terkecil)\n");
    printf("2. Turun (Z-A / terbaru / terbesar)\n");
    *arah = bacaAngka("Pilih arah: ", 1, 2);
}

static void tampilkanKatalog(int hanyaTersedia)
{
    int kriteria, arah, algoritma, jumlah, i;
    char jawab[8];
    Buku **daftar;

    pilihPengurutan(&kriteria, &arah, &algoritma);
    daftar = siapkanKatalog(hanyaTersedia, &jumlah, kriteria, arah, algoritma);

    if (daftar == NULL)
    {
        printf("\nTidak ada buku untuk ditampilkan.\n");
        return;
    }

    printf("\nDiurutkan: %s (%s) memakai %s, total %d buku\n\n",
           NAMA_KRITERIA[kriteria], arah == NAIK ? "naik" : "turun",
           NAMA_ALGORITMA[algoritma], jumlah);

    cetakHeaderBuku();
    for (i = 0; i < jumlah; i++)
    {
        cetakBarisBuku(i + 1, daftar[i]);

        if ((i + 1) % PER_HALAMAN == 0 && i + 1 < jumlah)
        {
            bacaBaris("-- Enter untuk lanjut, q untuk berhenti: ", jawab, sizeof(jawab));
            if (jawab[0] == 'q' || jawab[0] == 'Q')
            {
                break;
            }
        }
    }
    free(daftar);
}

static void menuCariBuku(void)
{
    char kata[64];

    bacaTeksWajib("Masukkan ID atau judul buku: ", kata, sizeof(kata));
    if (cariBuku(kata) == 0)
    {
        printf("Buku tidak ditemukan.\n");
    }
}

/* ---------- fitur admin ---------- */

static void menuTambahBuku(void)
{
    Buku b;

    printf("\n-- Tambah Buku --\n");
    bacaTanpaSpasi("ID buku (tanpa spasi): ", b.ocaid, sizeof(b.ocaid));

    if (cariIndexBuku(b.ocaid) != -1)
    {
        printf("ID sudah dipakai buku lain.\n");
        return;
    }

    bacaTeksWajib("Judul: ", b.title, sizeof(b.title));
    bacaTeksWajib("Pengarang: ", b.author, sizeof(b.author));
    gantiPetik(b.title);
    gantiPetik(b.author);
    b.year = bacaAngka("Tahun terbit: ", 1, 2100);
    b.page_count = bacaAngka("Jumlah halaman: ", 1, 100000);
    bacaTanpaSpasi("Openlibrary edition (tanpa spasi): ", b.openlibrary_edition,
                   sizeof(b.openlibrary_edition));
    bacaTanpaSpasi("Openlibrary work (tanpa spasi): ", b.openlibrary_work,
                   sizeof(b.openlibrary_work));
    bacaTanpaSpasi("Link teks lengkap / url (tanpa spasi): ", b.full_text_url,
                   sizeof(b.full_text_url));
    b.stok = bacaAngka("Stok: ", 0, 1000);

    if (tambahBuku(b))
    {
        printf("Buku berhasil ditambahkan.\n");
    }
    else
    {
        printf("Buku gagal ditambahkan.\n");
    }
}

static void menuUbahBuku(void)
{
    char id[64], teks[256];
    int idx, pilihan, tambahan;

    bacaTeksWajib("ID buku yang diubah: ", id, sizeof(id));
    idx = cariIndexBuku(id);
    if (idx == -1)
    {
        printf("Buku tidak ditemukan.\n");
        return;
    }

    do
    {
        cetakDetailBuku(&dataBuku[idx]);
        printf("\nYang ingin diubah:\n");
        printf("1. Judul\n2. Pengarang\n3. Tahun terbit\n");
        printf("4. Jumlah halaman\n5. Stok (tambah/kurangi)\n0. Selesai\n");
        pilihan = bacaAngka("Pilihan: ", 0, 5);

        if (pilihan == 1)
        {
            bacaTeksWajib("Judul baru: ", teks, sizeof(teks));
            gantiPetik(teks);
            snprintf(dataBuku[idx].title, sizeof(dataBuku[idx].title), "%s", teks);
        }
        else if (pilihan == 2)
        {
            bacaTeksWajib("Pengarang baru: ", teks, sizeof(teks));
            gantiPetik(teks);
            snprintf(dataBuku[idx].author, sizeof(dataBuku[idx].author), "%s", teks);
        }
        else if (pilihan == 3)
        {
            dataBuku[idx].year = bacaAngka("Tahun terbit baru: ", 1, 2100);
        }
        else if (pilihan == 4)
        {
            dataBuku[idx].page_count = bacaAngka("Jumlah halaman baru: ", 1, 100000);
        }
        else if (pilihan == 5)
        {
            tambahan = bacaAngka("Tambah/kurangi stok (contoh 3 atau -2): ", -1000, 1000);
            if (dataBuku[idx].stok + tambahan < 0)
            {
                printf("Stok tidak boleh kurang dari 0.\n");
                continue;
            }
            dataBuku[idx].stok += tambahan;
        }

        if (pilihan != 0)
        {
            simpanBuku();
            printf("Data berhasil diperbarui.\n");
        }
    } while (pilihan != 0);
}

static void menuHapusBuku(void)
{
    char id[64], yakin[8];
    int idx;

    bacaTeksWajib("ID buku yang dihapus: ", id, sizeof(id));
    idx = cariIndexBuku(id);
    if (idx == -1)
    {
        printf("Buku tidak ditemukan.\n");
        return;
    }

    cetakDetailBuku(&dataBuku[idx]);
    bacaBaris("\nYakin hapus buku ini? (y/n): ", yakin, sizeof(yakin));
    if (yakin[0] != 'y' && yakin[0] != 'Y')
    {
        printf("Dibatalkan.\n");
        return;
    }

    if (hapusBuku(idx))
    {
        printf("Buku berhasil dihapus.\n");
    }
    else
    {
        printf("Buku tidak bisa dihapus karena masih ada yang meminjam.\n");
    }
}

static void menuLaporan(void)
{
    printf("\n-- Laporan Peminjaman --\n\n");
    if (tampilPinjaman(NULL, 0) == 0)
    {
        printf("Belum ada transaksi peminjaman.\n");
    }
}

static void menuAdmin(User *user)
{
    int pilihan;

    do
    {
        printf("\n=== MENU ADMIN (%s) ===\n", user->username);
        printf("1. Lihat katalog buku\n");
        printf("2. Cari buku\n");
        printf("3. Tambah buku\n");
        printf("4. Ubah buku\n");
        printf("5. Hapus buku\n");
        printf("6. Laporan peminjaman\n");
        printf("0. Logout\n");
        pilihan = bacaAngka("Pilihan: ", 0, 6);

        switch (pilihan)
        {
        case 1:
            tampilkanKatalog(0);
            break;
        case 2:
            menuCariBuku();
            break;
        case 3:
            menuTambahBuku();
            break;
        case 4:
            menuUbahBuku();
            break;
        case 5:
            menuHapusBuku();
            break;
        case 6:
            menuLaporan();
            break;
        }
    } while (pilihan != 0);
}



// cuman ada di user bukan admin
static void menuPinjam(User *user)
{
    char id[64];

    bacaTeksWajib("ID buku yang ingin dipinjam: ", id, sizeof(id));
    switch (pinjamBuku(user->username, id))
    {
    case PINJAM_OK:
        printf("Buku berhasil dipinjam.\n");
        break;
    case PINJAM_BUKU_TIDAK_ADA:
        printf("Buku dengan ID tersebut tidak ada.\n");
        break;
    case PINJAM_STOK_HABIS:
        printf("Stok buku sedang habis.\n");
        break;
    case PINJAM_SUDAH_DIPINJAM:
        printf("Kamu sedang meminjam buku ini.\n");
        break;
    default:
        printf("Peminjaman gagal.\n");
    }
}

static void menuKembali(User *user)
{
    char id[64];

    bacaTeksWajib("ID buku yang dikembalikan: ", id, sizeof(id));
    if (kembalikanBuku(user->username, id))
    {
        printf("Buku berhasil dikembalikan.\n");
    }
    else
    {
        printf("Kamu tidak sedang meminjam buku dengan ID tersebut.\n");
    }
}

static void menuPinjamanSaya(User *user)
{
    printf("\n-- Buku yang sedang kamu pinjam --\n\n");
    if (tampilPinjaman(user->username, 1) == 0)
    {
        printf("Tidak ada buku yang sedang dipinjam.\n");
    }
}

static void menuUser(User *user)
{
    int pilihan;

    do
    {
        printf("\n=== MENU USER (%s) ===\n", user->username);
        printf("1. Lihat katalog buku tersedia\n");
        printf("2. Cari buku\n");
        printf("3. Pinjam buku\n");
        printf("4. Kembalikan buku\n");
        printf("5. Daftar pinjaman saya\n");
        printf("0. Logout\n");
        pilihan = bacaAngka("Pilihan: ", 0, 5);

        switch (pilihan)
        {
        case 1:
            tampilkanKatalog(1);
            break;
        case 2:
            menuCariBuku();
            break;
        case 3:
            menuPinjam(user);
            break;
        case 4:
            menuKembali(user);
            break;
        case 5:
            menuPinjamanSaya(user);
            break;
        }
    } while (pilihan != 0);
}

void jalankanMenu(User *user)
{
    if (adalahAdmin(user))
    {
        menuAdmin(user);
    }
    else
    {
        menuUser(user);
    }
    printf("\nKamu sudah logout.\n");
}