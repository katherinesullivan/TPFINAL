#include "operaciones.h"
#include "conjunto.h"
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define bool int

ITree itree_union (ITree cjto1, ITree cjto2, int band) { // paasar con 1 al principio
    ITree cjto3;
    if (band) {
        cjto3 = itree_clonar(cjto1);
    }
    else {
        cjto3 = cjto1;
    }
    // VER DSP DE BORARA ESTO
    if (cjto2 == NULL) {
        return cjto3;
    }
    else {
        cjto3 = itree_insertar(cjto3, cjto2->inte->inicio, cjto2->inte->fin, cjto3);
        cjto3 = itree_union(cjto3, cjto2->der, 0);
        cjto3 = itree_union(cjto3, cjto2->izq, 0);
    }
    return cjto3;
}


// CHEQUEAR SI TENGO QUE SEGUIR BUSCANDO
ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto) {
    if (nodo == NULL) {
        return cjto;
    }
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
    cjto = itree_comunes(nodo->der, inicio, final, cjto);
    cjto = itree_comunes(nodo->izq, inicio, final, cjto);
    
    
    return cjto;
}


ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjtoint) {
     // pasar como 1 al ppcio
     ITree cjto3;
     cjto3 = cjtoint;
     if (cjto2 == NULL) {
         return cjtoint;
     }
     else {
         cjto3 = itree_comunes(cjto1, cjto2->inte->inicio, cjto2->inte->fin, cjto3);
         // inicio fin recorrn todo el arbolito buscando interseciones
         cjto3 = itree_inter(cjto1, cjto2->der, cjto3);
         cjto3 = itree_inter(cjto1, cjto2->izq, cjto3);
     }
     
     return cjto3;
}


/* UTILITY FUNCTIONS */
/* Function to push an item to sNode*/
void push(struct sNode** top_ref, ITree t) 
{ 
/* allocate tNode */
struct sNode* new_tNode = 
			(struct sNode*) malloc(sizeof(struct sNode)); 

if(new_tNode == NULL) 
{ 
	printf("Stack Overflow \n"); 
	getchar(); 
	exit(0); 
}			 

/* put in the data */
new_tNode->t = t; 

/* link the old list off the new tNode */
new_tNode->next = (*top_ref); 

/* move the head to point to the new tNode */
(*top_ref) = new_tNode; 
} 

/* The function returns true if stack is empty, otherwise false */
bool isEmpty(struct sNode *top) 
{ 
return (top == NULL)? 1 : 0; 
} 

/* Function to pop an item from stack*/
ITree pop(struct sNode** top_ref) 
{ 
ITree res; 
struct sNode *top; 

/*If sNode is empty then error */
if(isEmpty(*top_ref)) 
{ 
	printf("Stack Underflow \n"); 
	getchar(); 
	exit(0); 
} 
else
{ 
	top = *top_ref; 
	res = top->t; 
	*top_ref = top->next; 
	free(top); 
	return res; 
} 
} 

/* Iterative function for inorder tree traversal */
ITree itree_comp(ITree root) { 

if(root == NULL){
    ITree comp = itree_crear();
    comp = itree_insertar(comp, INT_MIN, INT_MAX, comp);
    return comp;
}

/* set current to root of binary tree */
ITree current = root; 
struct sNode *s = NULL; /* Initialize stack s */
bool done = 0;
bool band = 1;
ITree comp;
int inicio = INT_MIN;

while (!done) { 
    /* Reach the left most tNode of the current tNode */
    if(current != NULL) 
    { 
    /* place pointer to a tree node on the stack before traversing 
        the node's left subtree */
    push(&s, current);											 
    current = current->izq; 
    } 
        
    /* backtrack from the empty subtree and visit the tNode 
    at the top of the stack; however, if the stack is empty, 
    you are done */
    else															
    { 
    if (!isEmpty(s)) 
    { 
        current = pop(&s); 
        if (band) {
            comp = itree_insertar(NULL, inicio, current->inte->inicio -1, NULL);
            band = 0;
        }
        else {
            comp = itree_insertar(comp, inicio, current->inte->inicio -1, comp);
        }
        inicio = current->inte->fin +1;

        /* we have visited the node and its left subtree. 
        Now, it's right subtree's turn */
        current = current->der; 
    } 
    else
        done = 1; 
    }
}
itree_insertar(comp, inicio, INT_MAX, comp);
return comp;
}

ITree itree_diferencia (ITree cjto1, ITree cjto2) {
    ITree dif = itree_inter(itree_comp(cjto2), cjto1, NULL);
    return dif;
}

// no free para itree_comp(cjto2) e igual sigo teniendo un temita de memoria