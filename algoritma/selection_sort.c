#include "selection_sort.h"

/*
 * Selection sort: cari elemen yang paling pantas berada di posisi i
 * dari sisa data, lalu tukar ke posisi i.
 */
void selectionSort(Buku **arr, int n, int kriteria, int arah) {
    int i, j, terpilih;
    Buku *temp;

    for (i = 0; i < n - 1; i++) {
        terpilih = i;
        for (j = i + 1; j < n; j++) {
            if (harusTukar(arr[terpilih], arr[j], kriteria, arah)) {
                terpilih = j;
            }
        }
        if (terpilih != i) {
            temp = arr[i];
            arr[i] = arr[terpilih];
            arr[terpilih] = temp;
        }
    }
}
