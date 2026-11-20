#ifndef MODELS_H // if not defined, Jika belum didefinisikan, lanjutkan membaca kode. Jika sudah didefinisikan, lewati kode sampai #endif.

#define MODELS_H

#define FILE_BUKU "data/Books.txt"
#define FILE_USER "data/User.txt"
#define FILE_PINJAM "data/Peminjaman.txt"

#define STOK_AWAL 5

typedef struct {
    char ocaid[64];
    char title[256];
    char author[256];
    int year;
    int page_count;
    char openlibrary_edition[32];
    char openlibrary_work[32];
    char full_text_url[256];
    int stok;
} Buku;

typedef struct {
    char username[32];
    char password[32];
    char role[12];
} User;

typedef struct {
    unsigned int id_peminjaman;
    char username[32];
    char ocaid[64];
    char tanggal_pinjam[20];
    char status[20];
} Peminjaman;

// membuat variabel global, agar file lain dalam project bisa menggunakan data yang sama
extern Buku *dataBuku;
extern int jumlahBuku;
extern User *dataUser;
extern int jumlahUser;
extern Peminjaman *dataPinjam;
extern int jumlahPinjam;

// function prototipenya
/* return 1 kalau berhasil, 0 kalau gagal */
int muatSemuaData(void);
void bebaskanSemuaData(void);

int tambahBukuKeMemori(Buku b);
int tambahPinjamKeMemori(Peminjaman p);

void simpanBuku(void);
void simpanPinjam(void);

#endif
