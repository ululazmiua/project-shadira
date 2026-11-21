#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"

Buku *dataBuku = NULL;
int jumlahBuku = 0;

User *dataUser = NULL;
int jumlahUser = 0;

Peminjaman *dataPinjam = NULL;
int jumlahPinjam = 0;

/*
Mengambil satu kata dari baris.
Jika menggunakan tanda petik, ambil seluruh teks di dalamnya.
Return 0 jika tidak ada kata.
*/
static int ambilKata(char *teks, int *pos, char *hasil, int maks)
{
    int i = 0;
 
    // Lewati spasi dan tab
    while (teks[*pos] == ' ' || teks[*pos] == '\t')
    {
        (*pos)++;
    }

    // Periksa apakah teks sudah habis
    if (teks[*pos] == '\0' || teks[*pos] == '\n')
    {
        return 0;
    }

    // Periksa apakah kata menggunakan tanda petik
    if (teks[*pos] == '"')
    {
        // untuk melewati tanda "
        (*pos)++;

        // Ambil teks sampai menemukan tanda petik penutup
        while (teks[*pos] != '"' && teks[*pos] != '\0' &&
               teks[*pos] != '\n' && teks[*pos] != '\r')
        {

            if (i < maks - 1)
            {
                // buku.ocaid[32] w w _ _ _
                hasil[i++] = teks[*pos];
            }

            (*pos)++;
        }

        // Lewati tanda petik penutup
        if (teks[*pos] == '"')
        {
            (*pos)++;
        }
    }
    // ini untuk membaca data yang bukan diapit sama tanda kutip "
    else
    {

        // Ambil kata biasa sampai menemukan spasi
        while (teks[*pos] != ' ' && teks[*pos] != '\t' &&
               teks[*pos] != '\0' && teks[*pos] != '\n' &&
               teks[*pos] != '\r')
        {

            if (i < maks - 1)  
            {
                // w w _ 
                // 0 1 2
                hasil[i++] = teks[*pos];
            }

            (*pos)++;
        }
    }

    // Akhiri string
    hasil[i] = '\0'; 

    return 1;
}

// Menambahkan buku ke dalam memori
int tambahBukuKeMemori(Buku b)
{
    Buku *baru = realloc(dataBuku, (jumlahBuku + 1) * sizeof(Buku)); // realloc(pointer, ukuran_baru); => digunakan untuk mengubah ukuran memori yang sebelumnya sudah dialokasikan secara dinamis.

    // jika null maka berarti gagal mendapatkan memori
    if (baru == NULL)
    {
        return 0;
    }

    // jika berhasil maka perbarui dataBuku
    dataBuku = baru;
    dataBuku[jumlahBuku] = b;
    jumlahBuku++;

    return 1;
}

// Menambahkan user ke dalam memori
static int tambahUserKeMemori(User u)
{
    User *baru = realloc(dataUser, (jumlahUser + 1) * sizeof(User));

    if (baru == NULL)
    {
        return 0;
    }

    dataUser = baru;
    dataUser[jumlahUser] = u;
    jumlahUser++;

    return 1;
}

// Menambahkan peminjaman ke dalam memori
int tambahPinjamKeMemori(Peminjaman p)
{
    Peminjaman *baru = realloc(dataPinjam, (jumlahPinjam + 1) * sizeof(Peminjaman));

    if (baru == NULL)
    {
        return 0;
    }

    dataPinjam = baru;
    dataPinjam[jumlahPinjam] = p;
    jumlahPinjam++;

    return 1;
}

// Membaca data buku dari file
static int muatBuku(void)
{
    FILE *f = fopen(FILE_BUKU, "r");

    char baris[2048];
    char tahun[32], halaman[32], stok[32];

    int pos; // menyimpan posisi karakter yang sedang dibaca
    Buku b;  // untuk menampung data buku sementara

    if (f == NULL)
    {
        printf("File %s tidak ditemukan.\n", FILE_BUKU);
        return 0;
    }

    while (fgets(baris, sizeof(baris), f) != NULL) // fgets(variabel_tujuan, ukuran_maksimal, file);
    {

        // Mulai membaca dari karakter pertama
        // Karena setiap kali membaca baris baru, kita harus memulai pengambilan kata dari karakter pertama.
        pos = 0;

        if (ambilKata(baris, &pos, b.ocaid, sizeof(b.ocaid)) &&
            ambilKata(baris, &pos, b.title, sizeof(b.title)) &&
            ambilKata(baris, &pos, b.author, sizeof(b.author)) &&
            ambilKata(baris, &pos, tahun, sizeof(tahun)) &&
            ambilKata(baris, &pos, halaman, sizeof(halaman)) &&
            ambilKata(baris, &pos, b.openlibrary_edition, sizeof(b.openlibrary_edition)) &&
            ambilKata(baris, &pos, b.openlibrary_work, sizeof(b.openlibrary_work)) &&
            ambilKata(baris, &pos, b.full_text_url, sizeof(b.full_text_url)))
        {

            // Lewati baris judul kolom
            if (strcmp(b.ocaid, "ocaid") == 0)
            {
                continue;
            }

            // Ubah teks menjadi angka
            b.year = atoi(tahun);
            b.page_count = atoi(halaman);

            // Ambil stok buku
            if (ambilKata(baris, &pos, stok, sizeof(stok)))
            {
                b.stok = atoi(stok);
            }
            else
            {
                b.stok = STOK_AWAL;
            }

            // Simpan buku ke memori
            if (!tambahBukuKeMemori(b))
            {
                printf("Memori tidak cukup.\n");
                fclose(f);
                return 0;
            }
        }
    }

    fclose(f);
    return 1;
}

// Membaca data user dari file
static int muatUser(void)
{
    FILE *f = fopen(FILE_USER, "r");

    char baris[256];
    int pos;

    User u;

    if (f == NULL)
    {
        printf("File %s tidak ditemukan.\n", FILE_USER);
        return 0;
    }

    while (fgets(baris, sizeof(baris), f) != NULL)
    {

        // Mulai dari karakter pertama
        pos = 0;

        if (ambilKata(baris, &pos, u.username, sizeof(u.username)) &&
            ambilKata(baris, &pos, u.password, sizeof(u.password)) &&
            ambilKata(baris, &pos, u.role, sizeof(u.role)))
        {

            // Lewati baris judul kolom
            if (strcmp(u.username, "username") == 0)
            {
                continue;
            }

            // Simpan user ke memori
            if (!tambahUserKeMemori(u))
            {
                printf("Memori tidak cukup.\n");
                fclose(f);
                return 0;
            }
        }
    }

    fclose(f);
    return 1; // menandakan berhasil
}

// Membaca data peminjaman dari file
static int muatPinjam(void)
{
    FILE *f = fopen(FILE_PINJAM, "r");

    char baris[256];
    char id[32];

    int pos;
    Peminjaman pj;

    // Jika file belum ada, anggap belum ada transaksi
    if (f == NULL)
    {
        return 1;
    }

    while (fgets(baris, sizeof(baris), f) != NULL)
    {

        // Mulai dari karakter pertama
        pos = 0;

        if (ambilKata(baris, &pos, id, sizeof(id)) &&
            ambilKata(baris, &pos, pj.username, sizeof(pj.username)) &&
            ambilKata(baris, &pos, pj.ocaid, sizeof(pj.ocaid)) &&
            ambilKata(baris, &pos, pj.tanggal_pinjam, sizeof(pj.tanggal_pinjam)) &&
            ambilKata(baris, &pos, pj.status, sizeof(pj.status)))
        {

            // Lewati baris judul kolom
            if (strcmp(id, "id_peminjaman") == 0)
            {
                continue;
            }

            // Ubah ID menjadi angka
            pj.id_peminjaman = (unsigned int)atoi(id);

            // Simpan peminjaman ke memori
            if (!tambahPinjamKeMemori(pj))
            {
                printf("Memori tidak cukup.\n");
                fclose(f);
                return 0;
            }
        }
    }

    fclose(f);
    return 1;
}

// Memuat semua data dari file
int muatSemuaData(void)
{
    if (!muatBuku() || !muatUser() || !muatPinjam())
    {
        bebaskanSemuaData();
        return 0;
    }

    return 1;
}

// Menyimpan data buku ke file
void simpanBuku(void)
{
    FILE *f = fopen(FILE_BUKU, "w");
    int i;

    if (f == NULL)
    {
        printf("Gagal menulis %s\n", FILE_BUKU);
        return;
    }

    fprintf(f, "ocaid title author year page_count openlibrary_edition "
               "openlibrary_work full_text_url stok\n");

    for (i = 0; i < jumlahBuku; i++)
    {
        fprintf(f, "%s \"%s\" \"%s\" %d %d %s %s %s %d\n",
                dataBuku[i].ocaid,
                dataBuku[i].title,
                dataBuku[i].author,
                dataBuku[i].year,
                dataBuku[i].page_count,
                dataBuku[i].openlibrary_edition,
                dataBuku[i].openlibrary_work,
                dataBuku[i].full_text_url,
                dataBuku[i].stok);
    }

    fclose(f);
}

// Menyimpan data peminjaman ke file
void simpanPinjam(void)
{
    FILE *f = fopen(FILE_PINJAM, "w");
    int i;

    if (f == NULL)
    {
        printf("Gagal menulis %s\n", FILE_PINJAM);
        return;
    }

    fprintf(f, "id_peminjaman username ocaid tanggal_pinjam status\n");

    for (i = 0; i < jumlahPinjam; i++)
    {
        fprintf(f, "%u %s %s %s %s\n",
                dataPinjam[i].id_peminjaman,
                dataPinjam[i].username,
                dataPinjam[i].ocaid,
                dataPinjam[i].tanggal_pinjam,
                dataPinjam[i].status);
    }

    fclose(f);
}

// Membebaskan semua memori yang digunakan
void bebaskanSemuaData(void)
{
    // realloc() untuk menambah kapasitas penyimpanan data buku. Ketika data tersebut sudah tidak diperlukan, memorinya bisa dibebaskan menggunakan free().
    free(dataBuku);
    free(dataUser);
    free(dataPinjam);

    // mengatur pointer dataBuku, dataUser, dan dataPinjam menjadi NULL, supaya tidak menyimpan alamat lama yang sudah tidak boleh digunakan.
    dataBuku = NULL;
    dataUser = NULL;
    dataPinjam = NULL;

    jumlahBuku = 0;
    jumlahUser = 0;
    jumlahPinjam = 0;
}