#include "conjunto.h"
#include "interprete.h"
#include "operaciones.h"
#include "tablahash.h"
#include <stdio.h>
#include <stdlib.h>

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 11 * hashval;
    return hashval;
}

unsigned hash2(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval;
}


int main() {
  int flag;
  TablaHash* diccionario = tablahash_crear(31, &hash, &hash2);
  /*char* a = malloc(sizeof(char)*5);
  a[0] = 'h';
  a[1] = 'o';
  a[2] = 'l';
  a[3] = 'a';

  ITree cjto = itree_crear();
  cjto = itree_insertar(NULL, 10, 10, NULL);
  cjto = itree_insertar(cjto, 11, 12, cjto);
  cjto = itree_insertar(cjto, 35, 100, cjto);
  cjto = itree_insertar(cjto, 13, 14, cjto);
  tablahash_insertar(diccionario, a, cjto);

  ITree cjto2 = tablahash_buscar(diccionario, a);
  itree_imprimir(cjto2);
  itree_recorrer_bfs(cjto2);*/

  char* buffer = malloc(100*sizeof(char));
  printf("Puede comenzar a escribir:\n");

  do {
    flag = parse_input(&diccionario, buffer);
  } while (flag == 1);

  tablahash_destruir(diccionario);
  free(buffer);
  return 0;
}