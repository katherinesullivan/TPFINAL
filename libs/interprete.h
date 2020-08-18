#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "tablahash.h"

int parse_input(TablaHash** diccionario, char* buffer);

int check_read(int process, int expected);

#endif /* __CONJUNTO_H__ */