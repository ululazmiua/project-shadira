#include "insertion_sort.h"


void insertionSort(Buku **arr, int n, int kriteria, int arah) {
    int i, j;
    Buku *kunci;

    for (i = 1; i < n; i++) {
        kunci = arr[i];
        j = i - 1;
        while (j >= 0 && harusTukar(arr[j], kunci, kriteria, arah)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}
