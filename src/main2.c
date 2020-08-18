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

  char* buffer = malloc(200*sizeof(char));
  printf("Puede comenzar a escribir:\n");

  do {
    flag = parse_input(&diccionario, buffer);
  } while (flag == 1);

  tablahash_destruir(diccionario);
  free(buffer);
  return 0;
}