#include "tablahash.h"
#include <stdlib.h>
#include <string.h>



/**
 * Crea una nueva tabla Hash vacía con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionHash hash2) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->hash2 = hash2;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
    tabla->tabla[idx].estado = 0;
  }

  return tabla;
}

/**
 * Inserta el dato en la tabla asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, char* clave, ITree dato) {
  int done = 0;
  int i = 0;

  while(!done) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    unsigned idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0 || tabla->tabla[idx].estado == 2) {
      // Si estaba vacío o eliminado el lugar, almacenamos los datos ingresados.
      tabla->tabla[idx].clave = clave;
      tabla->tabla[idx].dato = dato;
      tabla->tabla[idx].estado = 1;
      done = 1;
    }
    i++;
  }

  // Aumentamos la cantidad de elementos que hay
  tabla->numElems++;
  if (tabla->numElems/tabla->capacidad >= 0.75){
      tablahash_agrandar(tabla);
    }
}

/**
 * Busca el conjunto en la tabla asociado a la clave dada.
 * Si solover es 0, en caso de que esté presente devuelve un puntero al mismo, 
 * en caso contrario devuelve NULL.
 * Si solover es 1, devuelve NULL si no está presente, y un puntero
 * a su clave si lo está.
 */
void* tablahash_buscar (TablaHash* tabla, char* clave, int solover) {
  int done = 0;
  int i = 0;

  while(!done) {
    unsigned idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      done = 1;
      return NULL;
    }
    else if (strcmp(tabla->tabla[idx].clave, clave) == 0) {
      done = 1;
      if (solover) {
        return tabla->tabla[idx].clave;
        // para que no sea NULL si el cjto es vacío
      }
      return tabla->tabla[idx].dato;
    }
    i++;
  }
}

/**
 * Elimina el dato en la tabla asociado a la clave dada,
 * en caso de que este haya estado presente.
 */
void tablahash_eliminar (TablaHash* tabla, char* clave) {
  int done = 0;
  int i = 0;

  while(!done) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    unsigned idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      // Si llegamos a una casilla vacía es porque no estaba el elemento 
      done = 1;
    }
    else if (strcmp(tabla->tabla[idx].clave, clave) == 0) {
      // Si estaba, eliminamos y marcamos como eliminado el casillero
      free(tabla->tabla[idx].clave);
      itree_destruir(tabla->tabla[idx].dato);
      tabla->tabla[idx].estado = 2;
      // Disminuimos el nro de elementos 
      tabla->numElems--;
      done = 1;
    }
    i++;
  }
}

/**
 * Agranda una tabla de hash dada, aumentando su capacidad al doble más 9.
 * Esto nos asegura que empezando con una capacidad de 31, recién cuando
 * lleguemos a 1271 la capacidad de la tabla no será prima.
 */
TablaHash* tablahash_agrandar(TablaHash* tabla) {
  unsigned cap = tabla->capacidad;
  tabla->tabla = realloc(tabla->tabla, sizeof(CasillaHash) * (cap*2+9));

  // Inicializamos las casillas que agregamos con datos nulos.
  for (unsigned idx = cap; idx < cap*2+9; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
    tabla->tabla[idx].estado = 0;
  }

  tabla->capacidad = cap*2+9;

  return tabla;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  for (int i=0;i<tabla->capacidad;i++){
    itree_destruir(tabla->tabla[i].dato);
    free(tabla->tabla[i].clave);
  }
  free(tabla->tabla);
  free(tabla);
}