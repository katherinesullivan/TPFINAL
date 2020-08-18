#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stddef.h>

typedef struct
{
    int inicio;
    int fin;
} Intervalo;



typedef struct _ITNodo
{
    /*int inicio; // Inicio del intervalo
    int fin; // Final del intervalo*/
    Intervalo *inte; // Intervalo
    struct _ITNodo *izq; // Subárbol izquierdo
    struct _ITNodo *der; // Subárbol derecho
    int alt;
} ITNodo;

typedef ITNodo *ITree;

/**
 * Crea un árbol de intervalos vacío.
 */
ITree itree_crear();

/**
 * Destruye un árbol de intervalos.
 */
void itree_destruir(ITree tree);

/**
 * Devuelve la altura de un árbol de intervalos.
 */
int itree_altura(ITree nodo);

/**
 * Devuelve la diferencia de altura entre los hijos de un nodo
 * dentro de un árbol de intervalos.
 */
int itree_balance_factor (ITree nodo);

/**
 * Balancea un árbol de intervalos si este se encuentra 
 * desbalanceado.
 */
ITree hacer_avl(ITree raiz, int balance);

ITree nodo_clonar(int inicio, int final, int alt);

ITree itree_clonar (ITree nodo);

/**
 * Crea un nodo con los parámetros pasados.
 */
ITree nuevo_nodo(int inicio, int final);

/**
 * Inserta un intervalo en un árbol de intervalos.
 */
ITree itree_insertar(ITree nodo, int inicio, int final, ITree cjtoref);

/**
 * Se fija si determinado intervalo se encuentra en un árbol de intervalos.
 * Devuelve el nodo donde se encuentra en caso de estar presente o 
 * NULL en caso contratio
 */
ITree itree_search (ITree nodo, int inicio, int final);

/**
 * Encuentra el mínimo del subárbol derecho de un árbol dado.
 */
ITree min_subarbol_derecho(ITree nodo);

/**
 * Elimina un intervalo de un árbol de intervalos.
 */
ITree itree_eliminar_r(ITree nodo, int inicio, int final);

void itree_imprimir(ITree raiz, Intervalo* max);

Intervalo* maximo_inte(ITree raiz);

#endif /* __CONJUNTO_H__ */