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
    fgets(buffer, 99, stdin);

    // problema aca.
    sscanf(&buffer[0], "%s ", primera);
    printf("%s \n", primera);

    int idxbuf = strlen(primera);
    printf("%d\n", idxbuf);

    if (strcmp(primera, "salir") == 0){
        return 0;
    }

    if (strcmp(primera, "imprimir") == 0){
        char* alias = malloc(sizeof(char)*30);
        if (check_read(sscanf(&buffer[idxbuf+1], "%s", alias), 1)){
            if (tablahash_buscar(*diccionario, alias, 1) != NULL){
                ITree cjto = (ITree) tablahash_buscar(*diccionario, alias, 0);
                itree_imprimir(cjto);
            }
            else {
                printf("Conjunto inexistente. Verifique su entrada.\n");
            }
        }
    }

    else {
        char c;
        if (check_read(sscanf(&buffer[idxbuf+3], "%c", &c), 1)) {
            printf("%c\n", c);

            // Estoy creando un nuevo conjunto
            if (c == '{') {
                char a1;
                if (check_read(sscanf(&buffer[idxbuf+4], "%c", &a1), 1)){
                    printf("%c\n", a1);
                    if (a1 == 'x') {
                        // Por compresión
                        printf("comp\n");
                        int inicio;
                        int final;
                        if (check_read(
                        sscanf(&buffer[idxbuf+5], ": %d <= x <= %d}", &inicio, &final),
                        2)) {
                            printf("%d %d \n", inicio, final);
                            ITree cjto = itree_crear();
                            if (inicio <= final) {
                                cjto = itree_insertar(cjto, inicio, final, cjto);
                                itree_imprimir(cjto);
                            }
                            tablahash_insertar(*diccionario, primera, cjto);
                        }
                    }
                    else if (a1 == '}') {
                        ITree cjto = itree_crear();
                        tablahash_insertar(*diccionario, primera, cjto);
                    }
                    else {
                        // Por extensión
                        /*printf("entre");
                        const char coma[2] = ",";
                        char* token = malloc(sizeof(char)*100);
                        token = strtok(&buffer[idxbuf+4], coma);
                        printf("%s\n", token);
                        while (token != NULL) {
                            //char* elem = malloc(sizeof(char)*10);
                            //sscanf(token, "%s", elem);
                            ITree cjto = itree_crear();
                            cjto = itree_insertar(cjto, atoi(token), atoi(token), cjto);
                            tablahash_insertar(*diccionario, primera, cjto);
                            token = strtok(NULL, coma);
                        }*/
                        int elem;
                        if (check_read(sscanf(&buffer[idxbuf+4],"%d,%[^\n]\n", &elem, buffer),2)) {
                            ITree cjto = itree_crear();
                            cjto = itree_insertar(cjto, elem, elem, cjto);
                            while (sscanf(buffer,"%d,%[^\n]\n", &elem, buffer) == 2) {
                                cjto = itree_insertar(cjto, elem, elem, cjto);
                            }
                            if (strcmp(buffer, "}") != 0){
                                if (check_read(sscanf(buffer, "%d}", &elem), 1)) {
                                    cjto = itree_insertar(cjto, elem, elem, cjto);
                                }
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
                        // ver de hacerlo al reves mas optimo capaz
                        ITree cjto = (ITree) tablahash_buscar(*diccionario, alias, 0);
                        ITree cjto2 = itree_comp(cjto);
                        tablahash_insertar(*diccionario, primera, cjto2);
                    }
                    else {
                        printf("Conjunto inexistente. Verifique su entrada.\n");
                    }
                }
                /*else {
                    free(alias);
                }*/
            }

            // Voy a hacer una opercion q requiere de 2 cjtos
            else {
                char* alias1 = malloc(sizeof(char)*30);
                char* alias2 = malloc(sizeof(char)*30);
                char operador;
                if (check_read(
                sscanf(&buffer[idxbuf+3], "%s %c %s\n", alias1, &operador, alias2), 
                3)) {
                    printf("operador %c\n", operador);
                    if (tablahash_buscar(*diccionario, alias1, 1) != NULL &&
                        tablahash_buscar(*diccionario, alias2, 1) != NULL){
                        ITree cjto1 = (ITree) tablahash_buscar(*diccionario, alias1, 0);
                        ITree cjto2 = (ITree) tablahash_buscar(*diccionario, alias2, 0);
                        if (operador == '|') {
                            ITree cjto3 = itree_union(cjto1, cjto2, 1);
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }
                        else if (operador == '&') {
                            ITree cjto3 = itree_inter(cjto1, cjto2, NULL);
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }
                        else if (operador == '-') {
                            ITree cjto3 = itree_diferencia(cjto1, cjto2);
                            tablahash_insertar(*diccionario, primera, cjto3);
                        }
                        else {
                            printf("Entrada no válida. Verifique su operador");
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