#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__

#include <stddef.h>
#include "slist.h"
#include "conjunto.h"

#define bool int

/* Structure of a stack node. Linked List implementation is used for 
stack. A stack node contains a pointer to tree node and a pointer to 
next stack node */
struct sNode 
{ 
ITree t; 
struct sNode *next; 
}; 

/* Stack related functions */
void push (struct sNode** top_ref, ITree t); 
ITree pop (struct sNode** top_ref); 
bool isEmpty (struct sNode *top); 

ITree itree_comp (ITree root);
ITree itree_diferencia (ITree cjto1, ITree cjto2);

ITree itree_union (ITree cjto1, ITree cjto2, int band);

ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto);

ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjtoint);


#endif /* __CONJUNTO_H__ */