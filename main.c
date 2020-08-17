#include "operaciones.h"
#include "conjunto.h"
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

int main () {
    printf("empiezo");
    ITree cjto = itree_insertar(NULL, -1, -1, NULL);
    itree_insertar(cjto, -2, 3, cjto);
    cjto = itree_insertar(cjto, -58, -55, cjto);
    cjto = itree_insertar(cjto, -49, -48, cjto);
    cjto = itree_insertar(cjto, -57, -47, cjto);
    cjto = itree_insertar(cjto, -99, -89, cjto);
    itree_recorrer_bfs(cjto);
    printf("\n\n\n");

    ITree cjto2 = itree_insertar(NULL, -4, -1, NULL);
    cjto2 = itree_insertar(cjto2, -5, -2, cjto2);
    cjto2 = itree_insertar(cjto2, -100, -97, cjto2);
    cjto2 = itree_insertar(cjto2, -1, -1, cjto2);
    cjto2 = itree_insertar(cjto2, -57, -56, cjto2);
    cjto2 = itree_insertar(cjto2, -25, -25, cjto2);

    printf("\n\n\n");
    ITree cjto3 = itree_union(cjto, cjto2, 1);
    ITree cjto4 = itree_inter(cjto, cjto2, NULL);
    //ITree cjto5 = itree_diferencia(cjto, cjto2, NULL, 1);
    //ITree cjto6 = itree_complemento(cjto);
    itree_recorrer_bfs(cjto);
    printf("Hasta aca el 1 \n\n\n");
    itree_recorrer_bfs(cjto2);
    printf("Hasta aca el 2 \n\n\n");
    itree_recorrer_bfs(cjto3);
    printf("Hasta aca el 3 \n\n\n");
    itree_recorrer_bfs(cjto4);
    printf("Hasta aca el 4 \n\n\n");
    //itree_recorrer_bfs(cjto5);
    printf("Hasta aca el 5 \n\n\n");
    //itree_recorrer_bfs(cjto6);
    //printf("Hasta aca el 6 \n\n\n");
    //inOrder(cjto, INT_MIN);
    ITree cjto1 = itree_crear();
    itree_recorrer_bfs(itree_comp(cjto1));
    printf("\n\n\n");
    itree_imprimir(itree_diferencia(cjto, cjto2));
    printf("\n\n");
    itree_destruir(cjto);
    itree_destruir(cjto2);
    itree_destruir(cjto3);
    itree_destruir(cjto4);

    /*ITree cjto7 = itree_insertar(NULL, -1, 100, NULL);
    ITree cjto8 = itree_insertar(NULL, 3, 4, NULL);
    ITree cjto9 = itree_diferencia(cjto7, cjto8, NULL, 1);
    itree_recorrer_bfs(cjto9);
    printf("Hasta aca el 9\n");

    ITree A = itree_insertar(NULL, 0, 0, NULL);
    A = itree_insertar(A, 1, 1, A);
    A = itree_insertar(A, 2, 2, A);
    A = itree_insertar(A, 3, 3, A);
    printf("Conjunto A: \n");
    itree_recorrer_bfs(A);
    printf("\n\n\n");
    ITree B = itree_insertar(NULL, -3, 5, NULL);
    printf("Conjunto B: \n");
    itree_recorrer_bfs(B);
    printf("\n\n\n");
    ITree C = itree_insertar(NULL, 3, 7, NULL);
    printf("Conjunto C: \n");
    itree_recorrer_bfs(C);
    printf("\n\n\n");
    printf("AiB: \n");
    itree_recorrer_bfs(itree_inter(A, B, NULL));
    printf("\n\n\nBiA: \n");
    itree_recorrer_bfs(itree_inter(B, A, NULL));
    ITree resta1 = itree_diferencia(A, B, NULL, 1);
    printf("\nRESTA1 \n");
    itree_recorrer_bfs(resta1);
    printf("Resta2: \n");
    itree_recorrer_bfs(itree_diferencia(A, resta1, NULL, 1));
    printf("\n");
    ITree complemento = itree_complemento(cjto);
    printf("\ncomplemento \n");
    itree_recorrer_dfs(complemento);
    itree_recorrer_bfs(complemento);
    printf("\n");
    */

    return 0;
}

// PARA PRINTEAR DSP HACE UN INORDER Q TE LOS DEJA EN ORDEN XD 
// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/