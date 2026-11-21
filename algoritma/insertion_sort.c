#include "insertion_sort.h"


void insertionSort(Buku **arr, int jumlah_buku, int kriteria, int arah) {
    // i = menunjukkan posisi data yang sedang diambil untuk diurutkan.
    // j = digunakan untuk memeriksa data di sebelah kiri.
    // kunci = menyimpan sementara alamat buku yang sedang diproses.

    int i, j;
    Buku *kunci;

    // Perulangan ini digunakan untuk mengambil data satu per satu, dimulai dari indeks 1.
    // dimulai dari indeks 1, Karena data pada indeks 0 dianggap sudah terurut
    for (i = 1; i < jumlah_buku; i++) {
        kunci = arr[i];
        j = i - 1;
        while (j >= 0 && harusTukar(arr[j], kunci, kriteria, arah)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}
