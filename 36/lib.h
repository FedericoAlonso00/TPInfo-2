#ifndef _LIB
#define _LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos{
    char nombre[20];
    char apellido[20];
    char edad;
    long tel;
    char mail[40];
};

struct lista{
    struct datos d;
    struct lista *l;
};

#endif
