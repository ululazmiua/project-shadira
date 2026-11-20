#ifndef PEMBANDING_H
#define PEMBANDING_H

#include "../models.h"

/* kriteria pengurutan */
#define URUT_ID 1
#define URUT_JUDUL 2
#define URUT_TAHUN 3
#define URUT_HALAMAN 4
#define URUT_STOK 5

/* arah pengurutan */
#define NAIK 1
#define TURUN 2

/* banding dua teks tanpa melihat huruf besar/kecil */
int bandingkanTeks(const char *a, const char *b);

/* return 1 kalau a harus berada setelah b (urutannya terbalik) */
int harusTukar(const Buku *a, const Buku *b, int kriteria, int arah);

#endif
