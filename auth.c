#include <string.h>
#include "auth.h"

User *login(const char *username, const char *password) {
    int i;

    for (i = 0; i < jumlahUser; i++) {
        if (strcmp(dataUser[i].username, username) == 0
            && strcmp(dataUser[i].password, password) == 0) {
            return &dataUser[i];
        }
    }
    return NULL;
}

int adalahAdmin(const User *u) {
    return strcmp(u->role, "admin") == 0;
}
