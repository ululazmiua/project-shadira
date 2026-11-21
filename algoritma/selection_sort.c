#include "selection_sort.h"

/*
 * Selection sort: cari elemen yang paling pantas berada di posisi i
 * dari sisa data, lalu tukar ke posisi i.
 */
void selectionSort(Buku **arr, int jumlah_buku, int kriteria, int arah)
{
    
    // i = menunjukkan posisi yang sedang diisi.
    // j = digunakan untuk menampung posisi data lainnya yang mau diperiksa.
    // terpilih = menyimpan posisi data yang dianggap paling tepat.
    // temp = menyimpan sementara alamat buku saat menukar posisi.
    int i, j, terpilih;
    Buku *temp;

    for (i = 0; i < jumlah_buku - 1; i++)
    {
        terpilih = i;
        // bakalan mencari posisi data yang paling tepat (paling kecil/paling besar)
        for (j = i + 1; j < jumlah_buku; j++)
        {
            if (harusTukar(arr[terpilih], arr[j], kriteria, arah))
            {
                terpilih = j;
            }
        }

        // memeriksa apakah posisi data  yang terpilih itu berbeda dengan data yang di posisi i(data yang sedang diisi)
        if (terpilih != i)
        {
            temp = arr[i]; // Alamat buku pada posisi i disimpan sementara ke dalam variabel temp.
            arr[i] = arr[terpilih]; // Memindahkan alamat buku yang terpilih ke posisi i.
            arr[terpilih] = temp;   // Memindahkan alamat buku yang tadi disimpan di temp ke posisi terpilih.
        }
    }
}
