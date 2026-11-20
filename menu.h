#ifndef MENU_H
#define MENU_H

#include "models.h"

/* tampilkan layar login, return user yang berhasil masuk atau NULL kalau keluar */
User *menuLogin(void);

/* buka menu sesuai role user, selesai kalau user memilih logout */
void jalankanMenu(User *user);

#endif
