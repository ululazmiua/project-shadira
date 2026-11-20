#include <stdio.h>
#include "models.h"
#include "menu.h"

int main(void)
{
    User *user;

    if (!muatSemuaData())
    {
        return 1;
    }

    /* ulangi: login -> menu -> logout, sampai user memilih keluar */
    while (1)
    {
        user = menuLogin();
        if (user == NULL)
        {
            break;
        }
        jalankanMenu(user);
    }

    bebaskanSemuaData();
    printf("Sampai jumpa.\n");
    return 0;
}

// gcc -Wall -Wextra -std=c99 -o perpustakaan main.c models.c auth.c buku.c menu.c algoritma/*.c