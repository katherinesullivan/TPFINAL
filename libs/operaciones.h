#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__

#include <stddef.h>
#include "conjunto.h"

#define bool int


// Estructura de un nodo perteneciente a una pila. 
// Implementación con listas simplemente enlazadas.
struct sNode 
{ 
ITree t; 
struct sNode *next; 
}; 


void push (struct sNode** top_ref, ITree t); 

ITree pop (struct sNode** top_ref); 

bool isEmpty (struct sNode *top); 

ITree itree_comp (ITree root);

ITree itree_diferencia (ITree cjto1, ITree cjto2);

ITree itree_union (ITree cjto1, ITree cjto2, int band);

ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto);

ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjtoint);

ITree itree_unionn (ITree cjto1, ITree cjto2, ITree cjtounion);


#endif /* __CONJUNTO_H__ */