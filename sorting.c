#include <stdio.h>

int main()
{
    int nilai[] = {5, 3};
    int sementara;

    printf("Sebelum: %d %d\n", nilai[0], nilai[1]);

    sementara = nilai[0]; // simpan
    nilai[0] = nilai[1];
    nilai[1] = sementara;

    printf("Sesudah: %d %d\n", nilai[0], nilai[1]);
    return 0;
}