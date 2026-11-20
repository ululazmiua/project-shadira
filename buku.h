#ifndef BUKU_H
#define BUKU_H

#include "models.h"

/* hasil pinjamBuku */
#define PINJAM_OK 0
#define PINJAM_BUKU_TIDAK_ADA 1
#define PINJAM_STOK_HABIS 2
#define PINJAM_SUDAH_DIPINJAM 3
#define PINJAM_GAGAL 4

/* ---- katalog buku ---- */
int cariIndexBuku(const char *ocaid);
int tambahBuku(Buku b);
int hapusBuku(int index);

/*
 * Buat daftar pointer buku yang sudah diurutkan.
 * algoritma: 1 bubble, 2 selection, 3 insertion.
 * Hasilnya harus di-free oleh pemanggil.
 */
Buku **siapkanKatalog(int hanyaTersedia, int *jumlah, int kriteria, int arah, int algoritma);

void cetakHeaderBuku(void);
void cetakBarisBuku(int no, const Buku *b);
void cetakDetailBuku(const Buku *b);

/* cari berdasarkan id atau judul, return jumlah yang ketemu */
int cariBuku(const char *kataKunci);

/* ---- peminjaman ---- */
int pinjamBuku(const char *username, const char *ocaid);
int kembalikanBuku(const char *username, const char *ocaid);

/* username NULL berarti semua user. return jumlah baris yang dicetak */
int tampilPinjaman(const char *username, int hanyaAktif);

#endif
