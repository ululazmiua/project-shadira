#include <ctype.h>
#include "pembanding.h"

int bandingkanTeks(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        int x = tolower((unsigned char) *a);
        int y = tolower((unsigned char) *b);

        if (x != y) {
            return x - y;
        }
        a++;
        b++;
    }
    return tolower((unsigned char) *a) - tolower((unsigned char) *b);
}

/* hasil negatif: a lebih kecil dari b, positif: a lebih besar */
static int bandingkan(const Buku *a, const Buku *b, int kriteria) {
    switch (kriteria) {
        case URUT_ID:
            return bandingkanTeks(a->ocaid, b->ocaid);
        case URUT_JUDUL:
            return bandingkanTeks(a->title, b->title);
        case URUT_TAHUN:
            return a->year - b->year;
        case URUT_HALAMAN:
            return a->page_count - b->page_count;
        case URUT_STOK:
            return a->stok - b->stok;

        // jika a - b hasilnya negatif, maka a lebih kecil dari b, artinya tidak perlu ditukar
        // jika a - b hasilnya positif, maka a lebih besar dari b, artinya perlu ditukar
    }
    return 0;
}

int harusTukar(const Buku *a, const Buku *b, int kriteria, int arah) {
    int hasil = bandingkan(a, b, kriteria);

    if (arah == NAIK) {
        return hasil > 0;
    }
    return hasil < 0;
}
