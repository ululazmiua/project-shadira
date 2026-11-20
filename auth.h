#ifndef AUTH_H
#define AUTH_H

#include "models.h"

/* return pointer ke user kalau cocok, NULL kalau salah */
User *login(const char *username, const char *password);

/* return 1 kalau role-nya admin */
int adalahAdmin(const User *u);

#endif
