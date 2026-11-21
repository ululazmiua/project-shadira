#include "bubble_sort.h"

/*
 * Bubble sort: bandingkan dua elemen yang bersebelahan,
 * kalau urutannya masih salah maka ditukar. Ulangi sampai tidak ada yang ditukar.
 */


void bubbleSort(Buku **arr, int jumlah_buku, int kriteria, int arah) { // ** artinya arr adalah pointer ke pointer Buku.
    int i, j, ada_tukar;
    Buku *temp;

    for (i = 0; i < jumlah_buku - 1; i++) {
        ada_tukar = 0;
        for (j = 0; j < jumlah_buku - i - 1; j++) {
            if (harusTukar(arr[j], arr[j + 1], kriteria, arah)) {
                temp = arr[j];
                arr[j] = arr[j + 1]; // ditukar posisi dengan data didepannya
                arr[j + 1] = temp; // lalu data yang didepan tadi ditukar dengan data yang di belakang tadi
                ada_tukar = 1;
            }
        }
        // jika tidak ada yang ditukar, maka sudah urut, dan break perulangannya
        if (!ada_tukar) {
            break;
        }
    }
}
