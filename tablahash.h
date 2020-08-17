#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stddef.h>
#include "conjunto.h"

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash)(char* clave);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  char* clave;
  ITree dato;
  int estado; // será 0 si esta libre, 1 si está ocupada, 2 si está eliminada
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionHash hash2;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionHash hash2);

/**
 * Inserta el dato en la tabla asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, char* clave, ITree dato);

/**
 * Busca el conjunto en la tabla asociado a la clave dada.
 * En caso de que esté presente devuelve un puntero al mismo, 
 * en caso contrario devuelve NULL.
 */
void* tablahash_buscar (TablaHash* tabla, char* clave, int solover);

/**
 * Elimina el dato en la tabla asociado a la clave dada,
 * en caso de que este haya estado presente.
 */
void tablahash_eliminar (TablaHash* tabla, char* clave);

/**
 * Agranda una tabla de hash dada, duplicando su capacidad.
 */
TablaHash* tablahash_agrandar(TablaHash* tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */