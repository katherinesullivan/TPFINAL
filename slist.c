#include "slist.h"
#include <stdlib.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

SList slist_agregar_final(SList lista, void* dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->tail = nuevoNodo;

  if (lista == NULL){
      return nuevoNodo;
  }

  /*SList nodo = lista->tail;
  lista->tail = nuevoNodo;
  nodo->sig = nuevoNodo;*/
  lista->tail->sig = nuevoNodo;
  lista->tail = lista->tail->sig;

  return lista;
}

SList slist_eliminar_inicio(SList lista) {
    SList nuevaLista = lista->sig;
    if (nuevaLista != NULL){
        nuevaLista->tail = lista->tail;
    }
    free(lista);
    return nuevaLista;
}