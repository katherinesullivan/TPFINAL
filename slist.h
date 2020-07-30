#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  void* dato;
  struct _SNodo *sig;
  struct _SNodo *tail;
} SNodo;

typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, void* dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_eliminar_inicio(SList lista);


#endif /* __SLIST_H__ */