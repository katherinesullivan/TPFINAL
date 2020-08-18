#include "interprete.h"
#include "conjunto.h"
#include "operaciones.h"
#include "tablahash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parse_input(TablaHash** diccionario, char* buffer) {
    char* primera = malloc(sizeof(char)*30);

    printf("\nnuevo comando\n");
    
    fgets(buffer, 199, stdin);

    sscanf(&buffer[0], "%s ", primera);

    int idxbuf = strlen(primera);

    if (strcmp(primera, "salir") == 0){
        free(primera);
        return 0;
    }

    if (strcmp(primera, "imprimir") == 0){
        char* alias = malloc(sizeof(char)*30);
        if (check_read(sscanf(&buffer[idxbuf+1], "%s", alias), 1)){
            if (tablahash_buscar(*diccionario, alias, 1) != NULL){
                ITree cjto = (ITree) tablahash_buscar(*diccionario, alias, 0);
                itree_imprimir(cjto, maximo_inte(cjto));
            }
            else {
                printf("Conjunto inexistente. Verifique su entrada.\n");
            }
        }
        free(primera);
        free(alias);
    }

    else {
        char asignacion;
        sscanf(&buffer[idxbuf], " %c ", &asignacion);
        if (asignacion != '=') {
            printf("Entrada inválidaa. Chequee los comandos permitidos en el README.\n");
            return 1;
        }
    
        char c;
        if (check_read(sscanf(&buffer[idxbuf+3], "%c", &c), 1)) {
            
            // Estoy creando un nuevo conjunto
            if (c == '{') {
                char a1;
                if (check_read(sscanf(&buffer[idxbuf+4], "%c", &a1), 1)){
                
                    if (a1 == 'x') {
                        // Por compresión
                        int inicio;
                        int final;
                        if (check_read(
                        sscanf(&buffer[idxbuf+5], ": %d <= x <= %d}", &inicio, &final),
                        2)) {
                            ITree cjto = itree_crear();
                            if (inicio <= final) {
                                cjto = itree_insertar(cjto, inicio, final, cjto);
                            }
                            // Antes de definir un conjunto queremos 
                            // chequear de que no exista
                            // uno con el mismo nombre
                            if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                                tablahash_eliminar(*diccionario, primera);
                            }
                            tablahash_insertar(*diccionario, primera, cjto);
                        }
                    }
                    else if (a1 == '}') {
                        // Vacío
                        ITree cjto = itree_crear();
                        // Antes de definir un conjunto queremos chequear de que no exista
                        // uno con el mismo nombre
                        if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                            tablahash_eliminar(*diccionario, primera);
                        }
                        tablahash_insertar(*diccionario, primera, cjto);
                    }
                    else {
                        // Por extensión
                        int elem;
                        if (check_read(
                        sscanf(&buffer[idxbuf+4],"%d%[^\n]\n", &elem, buffer),2)) {
                            ITree cjto = itree_crear();
                            cjto = itree_insertar(cjto, elem, elem, cjto);
                            while (sscanf(buffer,",%d%[^\n]\n", &elem, buffer) == 2) {
                                cjto = itree_insertar(cjto, elem, elem, cjto);
                            }
                            if (strcmp(buffer, "}") != 0){
                                if (check_read(sscanf(buffer, "%d}", &elem), 1)) {
                                    cjto = itree_insertar(cjto, elem, elem, cjto);
                                }
                            }
                            // Antes de definir un conjunto queremos chequear 
                            // de que no exista uno con el mismo nombre
                            if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                                tablahash_eliminar(*diccionario, primera);
                            }
                            tablahash_insertar(*diccionario, primera, cjto);
                        }
                    }
                }
            }

            // Voy a hacer un complemento
            else if (c == '~') {
                char* alias = malloc(sizeof(char)*30);
                if (check_read(sscanf(&buffer[idxbuf+4], "%s\n", alias), 1)) {
                    if (tablahash_buscar(*diccionario, alias, 1) != NULL) {
                        ITree cjto = (ITree) tablahash_buscar(*diccionario, alias, 0);
                        ITree cjto2 = itree_comp(cjto);
                        // Antes de definir un conjunto queremos chequear de que no exista
                        // uno con el mismo nombre
                        if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                            tablahash_eliminar(*diccionario, primera);
                        }
                        tablahash_insertar(*diccionario, primera, cjto2);
                    }
                    else {
                        printf("Conjunto inexistente. Verifique su entrada.\n");
                    }
                }
            }

            // Voy a hacer una opercion q requiere de 2 cjtos
            else {
                char* alias1 = malloc(sizeof(char)*30);
                char* alias2 = malloc(sizeof(char)*30);
                char operador;
                if (check_read(
                sscanf(&buffer[idxbuf+3], "%s %c %s\n", alias1, &operador, alias2), 
                3)) {
                    if (tablahash_buscar(*diccionario, alias1, 1) != NULL &&
                        tablahash_buscar(*diccionario, alias2, 1) != NULL){
                        ITree cjto1 = (ITree) tablahash_buscar(*diccionario, alias1, 0);
                        ITree cjto2 = (ITree) tablahash_buscar(*diccionario, alias2, 0);

                        // Unión
                        if (operador == '|') {
                            //ITree cjto3 = itree_union(cjto1, cjto2, 1);
                            ITree cjto3 = itree_crear();
                            cjto3 = itree_union(cjto1, cjto2, 1);
                            // Antes de definir un conjunto queremos chequear de 
                            // que no exista uno con el mismo nombre
                            if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                                tablahash_eliminar(*diccionario, primera);
                            }
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }

                        // Intersección
                        else if (operador == '&') {
                            ITree cjto3 = itree_inter(cjto1, cjto2, NULL);
                            // Antes de definir un conjunto queremos chequear de que
                            // no exista uno con el mismo nombre
                            if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                                tablahash_eliminar(*diccionario, primera);
                            }
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }

                        // Diferencia
                        else if (operador == '-') {
                            ITree cjto3 = itree_diferencia(cjto1, cjto2);
                            // Antes de definir un conjunto queremos chequear de 
                            // que no exista uno con el mismo nombre
                            if (tablahash_buscar(*diccionario, primera, 1) != NULL) {
                                tablahash_eliminar(*diccionario, primera);
                            }
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }
                        else {
                            printf("Entrada no válida. Verifique su operador.\n");
                        }
                    }
                    else {
                        printf("Conjunto inexistente. Verifique su entrada.\n");
                    }
                }
            }
        }
    }
    return 1;
}

int check_read(int process, int expected) {
    if (process == expected) {
        return 1;
    }
    printf("Entrada inválida. Chequee los comandos permitidos en el README.\n");
    return 0;
}