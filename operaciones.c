#include "operaciones.h"
#include "conjunto.h"
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_union (ITree cjto1, ITree cjto2, int band) { // paasar con 1 al principio
    ITree cjto3;
    if (band) {
        cjto3 = itree_clonar(cjto1);
    }
    else {
        cjto3 = cjto1;
    }
    if (cjto2 == NULL) {
        return cjto3;
    }
    else {
        cjto3 = itree_insertar(cjto3, cjto2->inicio, cjto2->fin);
        cjto3 = itree_union(cjto3, cjto2->der, 0);
        cjto3 = itree_union(cjto3, cjto2->izq, 0);
    }
    return cjto3;
}

ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto) {
    if (nodo == NULL) {
        return NULL;
    }
    if (nodo->inicio == inicio && nodo->fin == final) {
        cjto = itree_insertar(cjto, inicio, final);
    }
    else if (inicio <= nodo->inicio) {
        // Caso 1 { [ } ]
        if (final <= nodo->fin && nodo->inicio <= final) {
            cjto = itree_insertar(cjto, nodo->inicio, final);
        }
        // Caso 3 { [ ] }
        if (nodo->fin <= final) {
            cjto = itree_insertar(cjto, nodo->inicio, nodo->fin);
        }
    }
    else if (nodo->inicio <= inicio) {
        // Caso 2 [ { ] }
        if (inicio <= nodo->fin && nodo->fin <= final) {
            cjto = itree_insertar(cjto, inicio, nodo->fin);
        }
        // Caso 4 [ { } ]
        else if (final <= nodo->fin) {
            cjto = itree_insertar(cjto, inicio, final);
        }
    }
    cjto = itree_comunes(nodo->der, inicio, final, cjto);
    cjto = itree_comunes(nodo->izq, inicio, final, cjto);
    return cjto;
}

ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjto3) {
     // pasar con NULL al principio
     if (cjto2 == NULL) {
         return NULL;
     }
     else {
         cjto3 = itree_comunes(cjto1, cjto2->inicio, cjto2->fin, cjto3);
         // inicio fin recorrn todo el arbolito buscando interseciones
         cjto3 = itree_inter(cjto1, cjto2->der, cjto3);
         cjto3 = itree_inter(cjto1, cjto2->izq, cjto3);
     }
     return cjto3;
}