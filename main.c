#include "operaciones.h"
#include "conjunto.h"
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

int main () {
    ITree cjto = itree_insertar(NULL, 1, 1);
    cjto = itree_insertar(cjto, 2, 3);
    cjto = itree_insertar(cjto, 5, 6);
    cjto = itree_insertar(cjto, 98, 99);
    cjto = itree_insertar(cjto, 76, 78);
    cjto = itree_insertar(cjto, -5, -5);
    cjto = itree_insertar(cjto, 30, 33);
    cjto = itree_insertar(cjto, 8, 8);
    cjto = itree_insertar(cjto, 0, 0);
    ITree cjto2 = itree_insertar(NULL, 2, 3);
    cjto2 = itree_insertar(cjto2, 3, 4);
    cjto2 = itree_insertar(cjto2, 9, 10);
    cjto2 = itree_insertar(cjto2, 97, 100);
    cjto2 = itree_insertar(cjto2, -1, 0);
    cjto2 = itree_insertar(cjto2, 56, 57);
    cjto2 = itree_insertar(cjto2, 25, 25);
    ITree cjto3 = itree_union(cjto, cjto2, 1);
    ITree cjto4 = itree_inter(cjto, cjto2, NULL);
    itree_recorrer_bfs(cjto);
    printf("Hasta aca el 1 \n\n\n");
    itree_recorrer_bfs(cjto2);
    printf("Hasta aca el 2 \n\n\n");
    itree_recorrer_bfs(cjto3);
    printf("Hasta aca el 3 \n\n\n");
    itree_recorrer_bfs(cjto4);
    return 0;
}