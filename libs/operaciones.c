#include "operaciones.h"
#include "conjunto.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define bool int

ITree itree_union (ITree cjto1, ITree cjto2, int band) { // paasar con 1 al principio
    ITree cjto3;
    if (band) {
        // Si llamo por fuera de esta función a unión,
        // copio todos los elementos del primer cjto al
        // cjto a devolver
        cjto3 = itree_clonar(cjto1);
    }
    else {
        cjto3 = cjto1;
    }
    if (cjto2 == NULL) {
        return cjto3;
    }
    else {
        // Voy insertando todos los del cjto2
        cjto3 = itree_insertar(cjto3, cjto2->inte->inicio, cjto2->inte->fin, cjto3);
        cjto3 = itree_union(cjto3, cjto2->der, 0);
        cjto3 = itree_union(cjto3, cjto2->izq, 0);
    }
    return cjto3;
}


ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto) {
    if (nodo == NULL) {
        return cjto;
    }

    // Vemos como intersecan

    else if (nodo->inte->inicio == inicio && nodo->inte->fin == final) {
        cjto = itree_insertar(cjto, inicio, final, cjto);
    }
    else if (inicio <= nodo->inte->inicio) {
        // Caso 1 { [ } ]
        if (final <= nodo->inte->fin && nodo->inte->inicio <= final) {
            cjto = itree_insertar(cjto, nodo->inte->inicio, final, cjto);
        }
        // Caso 3 { [ ] }
        else if (nodo->inte->fin <= final) {
            cjto = itree_insertar(cjto, nodo->inte->inicio, nodo->inte->fin, cjto);
        }
    }
    else if (nodo->inte->inicio <= inicio) {
        // Caso 2 [ { ] }
        if (inicio <= nodo->inte->fin && nodo->inte->fin <= final) {
            cjto = itree_insertar(cjto, inicio, nodo->inte->fin, cjto);
        }
        // Caso 4 [ { } ]
        else if (final <= nodo->inte->fin) {
            cjto = itree_insertar(cjto, inicio, final, cjto);
        }
    }

    // Sigo con el mismo intervalo recorriendo el árbol
    cjto = itree_comunes(nodo->der, inicio, final, cjto);
    cjto = itree_comunes(nodo->izq, inicio, final, cjto);
    
    
    return cjto;
}


ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjtoint) {
     ITree cjto3;
     cjto3 = cjtoint;
     if (cjto2 == NULL) {
         return cjtoint;
     }
     else {
         cjto3 = itree_comunes(cjto1, cjto2->inte->inicio, cjto2->inte->fin, cjto3);
         // inicio y fin recorren todo el cjto1 buscando interseciones
         cjto3 = itree_inter(cjto1, cjto2->der, cjto3);
         // hacemos lo mismo con el subarbol derecho
         cjto3 = itree_inter(cjto1, cjto2->izq, cjto3);
         // y con el izquierdo
     }
     
     return cjto3;
}


// Función para pushear un elemento a la pila pasada
void push(struct sNode** top_ref, ITree t) { 
    // Pedimos memoria para el elemento
    struct sNode* new_tNode = 
                (struct sNode*) malloc(sizeof(struct sNode)); 

    if(new_tNode == NULL) { 
        printf("Stack Overflow \n"); 
        getchar(); 
        exit(0); 
    }			 

    // Ponemos la información
    new_tNode->t = t; 

    // Lo linkeamos a la lista vieja
    new_tNode->next = (*top_ref); 

    // Movemos el puntero del tope de la pila al elemento ingresado
    (*top_ref) = new_tNode; 
} 

// Función que devuelve 1 si la pila pasada es vacía, 0 si no.
bool isEmpty(struct sNode *top) { 
    return (top == NULL)? 1 : 0; 
} 

// Función para popear el elemento del tope de una pila
ITree pop(struct sNode** top_ref) { 
    ITree res; 
    struct sNode *top; 

    // Si está vacía tenemos un error
    if(isEmpty(*top_ref)) { 
        printf("Stack Underflow \n"); 
        getchar(); 
        exit(0); 
    } 
    else{ 
        top = *top_ref; 
        res = top->t; 
        *top_ref = top->next; 
        free(top); 
        return res; 
    } 
} 


ITree itree_comp(ITree root) { 

    if(root == NULL){
        ITree comp = itree_crear();
        comp = itree_insertar(comp, INT_MIN, INT_MAX, comp);
        return comp;
    }

    // Tomamos como nodo actual la raíz del árbol
    ITree current = root; 
    struct sNode *s = NULL; // Inicializamos la pila
    bool done = 0;
    bool band = 1;
    ITree comp;
    int inicio = INT_MIN;

    while (!done) { 
        // Nos vamos moviendo hasta el nodo más a la izquierda del árbol
        if(current != NULL) { 
            // Y mientras los vamos añadiendo a la pila
            push(&s, current);											 
            current = current->izq; 
        } 
            
        // Vamos trabajando con los elementos en el tope de la pila
        // hasta vaciarla
        else {
            if (!isEmpty(s)) { 
                current = pop(&s); 
                if (band) {
                    // Si estamos en el menor elemento, para crear comp
                    // le pasamos como parámetro al insertar conjuntos NULL
                    if (inicio != current->inte->inicio) {
                        comp = itree_insertar(NULL, inicio, current->inte->inicio -1, NULL);
                        band = 0;
                    }
                }
                else {
                    // Siempre chequeamos que no sean consecutivos los elementos
                    if (inicio != current->inte->inicio) {
                        comp = itree_insertar(comp, inicio, current->inte->inicio -1, comp);
                    }
                }
                // Seteamos el inicio del próximo intervalo
                inicio = current->inte->fin +1;

                // Como ya visitamos el nodo y su subárbol izquierdo, 
                // Ahora nos movemos al derecho.
                current = current->der; 
            }
            else
                done = 1; 
        }
    }
    // Insertamos el último intervalo
    itree_insertar(comp, inicio, INT_MAX, comp);
    return comp;
}

ITree itree_diferencia (ITree cjto1, ITree cjto2) {
    ITree dif = itree_inter(itree_comp(cjto2), cjto1, NULL);
    return dif;
}
