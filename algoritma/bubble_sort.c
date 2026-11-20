#include "bubble_sort.h"

/*
 * Bubble sort: bandingkan dua elemen yang bersebelahan,
 * kalau urutannya salah ditukar. Ulangi sampai tidak ada yang ditukar.
 */
void bubbleSort(Buku **arr, int n, int kriteria, int arah) {
    int i, j, ada_tukar;
    Buku *temp;

    for (i = 0; i < n - 1; i++) {
        ada_tukar = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (harusTukar(arr[j], arr[j + 1], kriteria, arah)) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                ada_tukar = 1;
            }
        }
        if (!ada_tukar) {
            break;
        }
    }
}
