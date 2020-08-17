#include "conjunto.h"
#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
}

void itree_destruir(ITree tree) {
  if (tree != NULL){
    itree_destruir(tree->izq);
    itree_destruir(tree->der);
    free(tree->inte);
    free(tree);
  }
}

int itree_altura(ITree N) {
  if (N == NULL) {
    return 0;
  }
  else {
    return N->alt;
  }
}

int itree_balance_factor(ITree N) {
  if (N == NULL) {
      return 0;
  }
  return itree_altura(N->izq) - itree_altura(N->der);
}

ITree right_rotate(ITree raiz) {
  ITree a = raiz->izq;
  ITree arbol3 = a->der;

  // Efectuamos las rotaciones
  raiz->izq = arbol3;
  a->der = raiz;

  // Actualizamos las alturas
  if (itree_altura(raiz->izq) > itree_altura(raiz->der)){
      raiz->alt = itree_altura(raiz->izq) + 1;
  }
  else{
      raiz->alt = itree_altura(raiz->izq) + 1;
  }
  if (itree_altura(a->der) > itree_altura(a->izq)){
      a->alt = itree_altura(a->der) + 1;
  }
  else{
      a->alt = itree_altura(a->izq) + 1;
  }

  return a;
}

ITree left_rotate(ITree raiz){
  ITree a = raiz->der;
  ITree arbol2 = a->izq;

  // Efectuamos las rotaciones
  raiz->der = arbol2;
  a->izq = raiz;

  // Actualizamos las alturas
  if (itree_altura(raiz->izq) > itree_altura(raiz->der)){
      raiz->alt = itree_altura(raiz->izq) + 1;
  }
  else{
      raiz->alt = itree_altura(raiz->der) + 1;
  }
  if (itree_altura(a->der) > itree_altura(a->izq)){
      a->alt = itree_altura(a->der) + 1;
  }
  else{
      a->alt = itree_altura(a->izq) + 1;
  }

  return a;
}

ITree hacer_avl(ITree raiz, int balance){
  // Contemplamos los posibles casos 

  // Caso izquierda
  if (balance > 1 && itree_balance_factor(raiz->izq) >= 0) {
    return right_rotate(raiz); 
  }
  // Caso izquierda derecha
  if (balance > 1 && itree_balance_factor(raiz->izq) < 0) { 
    raiz->izq =  left_rotate(raiz->izq); 
    return right_rotate(raiz); 
  }
  // Caso derecha
  if (balance < -1 && itree_balance_factor(raiz->der) <= 0) {
    return left_rotate(raiz); 
  }
  // Caso derecha izquierda
  if (balance < -1 && itree_balance_factor(raiz->der) > 0) { 
    raiz->der = right_rotate(raiz->der); 
    return left_rotate(raiz); 
  }
  return raiz; 
}


ITree nodo_clonar (int inicio, int final, int alt) {
    ITree nodo = malloc(sizeof(ITNodo));
    nodo->izq = NULL;
    nodo->der = NULL;
    Intervalo* inte = malloc(sizeof(Intervalo));
    nodo->inte = inte;
    nodo->inte->inicio = inicio;
    nodo->inte->fin = final;
    nodo->alt = alt;
    return nodo;
}


ITree itree_clonar (ITree nodo) {
    if (nodo == NULL) {
        return NULL;
    }
    ITree nuevo = nodo_clonar(nodo->inte->inicio, nodo->inte->fin, nodo->alt);
    nuevo->izq = itree_clonar(nodo->izq);
    nuevo->der = itree_clonar(nodo->der);
    return nuevo;
}


ITree nuevo_nodo(int inicio, int final) {
  // Pido un bloque de memoria
  ITree nodo = malloc(sizeof(ITNodo));
  // Al tratarse de una hoja, no tendrá hijos, su max será su final y su altura, 1
  nodo->izq = NULL;
  nodo->der = NULL;
  Intervalo* inte = malloc(sizeof(Intervalo));
  nodo->inte = inte;
  nodo->inte->inicio = inicio;
  nodo->inte->fin = final;
  nodo->alt = 1;
  return nodo;
}


ITree itree_insertar(ITree nodo, int inicio, int final, ITree cjtoref) {
  // cjto ref va a ser pasado como = nodo al principio y luego se mantendra

  // Si estamos en posición para agregar, agregamos el nodo como una hoja
  if (nodo == NULL) {
    return nuevo_nodo(inicio, final);
  }

  // PONER ANTES SI SON IGUALES BAI
  // Si no varía en valores significa que el nodo ya se encuentra en el árbol
  if (nodo->inte->inicio == inicio && nodo->inte->fin == final) {
    printf("El elemento ya se encuentra en el árbol \n");
    return nodo;
  }

  // COMO INTERSECA?
  if (inicio <= nodo->inte->inicio) {
      // Caso 1 { [ } ]
      if (nodo->inte->inicio <= final && final < nodo->inte->fin){
        if (nodo->der != NULL || nodo->izq != NULL) {
          final = nodo->inte->fin;
          itree_eliminar_r(cjtoref, nodo->inte->inicio, nodo->inte->fin);
          cjtoref = itree_insertar(cjtoref, inicio, final, cjtoref);
        }
        else {
          nodo->inte->inicio = inicio;
        }
      }
      // Caso 3 { [ ] }
      else if (nodo->inte->fin <= final) {
        if (nodo->der != NULL || nodo->izq != NULL) {
          itree_eliminar_r(cjtoref, nodo->inte->inicio, nodo->inte->fin);
          cjtoref = itree_insertar(cjtoref, inicio, final, cjtoref);
        }
        else {
          nodo->inte->inicio = inicio;
          nodo->inte->fin = final;
        }
      }
      // no interseca
      else if (final < nodo->inte->inicio) {
          nodo->izq = itree_insertar(nodo->izq, inicio, final, cjtoref);
      }
  }
  else if (nodo->inte->inicio <= inicio) {
      // Caso 2 [ { ] }
      if (inicio <= nodo->inte->fin && nodo->inte->fin < final){
          if (nodo->izq != NULL || nodo->der != NULL) {
            inicio = nodo->inte->inicio;
            itree_eliminar_r(cjtoref, inicio, nodo->inte->fin);
            //printf("\nelimine [%d, %d]\n", inicio, nodo->inte->fin);
            cjtoref = itree_insertar(cjtoref, inicio, final, cjtoref);
          }
          else {
            nodo->inte->fin = final;
          }
      }
      // Caso 4 [ { } ]
      else if (final <= nodo->inte->fin) {
        return nodo;
      }
      // no interseca
      else if (inicio > nodo->inte->fin) {
          nodo->der = itree_insertar(nodo->der, inicio, final, cjtoref);
      }
  }

  /*// Si no nos encontrabamos en posicion para agregar, según
  // cómo varía el intervalo respecto al del nodo donde estamos, vemos de 
  // ir por izquierda o por derecha
  else if (final < nodo->inicio) {
    nodo->izq = itree_insertar(nodo->izq, inicio, final);
  }
  else if (inicio > nodo->fin) {
    nodo->der = itree_insertar(nodo->der, inicio, final);
  }*/
  
  // Ajusto la altura de este antecesor al nodo agregado
  if (itree_altura(nodo->der) <= itree_altura(nodo->izq)) {
    nodo->alt = 1 + itree_altura(nodo->izq);
  }
  else {
    nodo->alt = 1 + itree_altura(nodo->der);
  }

  // Veo de balancear el arbol en caso de ser necesario
  int balance = itree_balance_factor(nodo);

  return (hacer_avl(nodo, balance));

}

ITree min_subarbol_derecho(ITree nodo) {
  ITree retorno;
  // Si el nodo derecho tiene un hijo izquierdo
  if (nodo->der->izq != NULL) {
    retorno = nodo->der->izq;
    while (retorno->izq != NULL) {
      // vamos recorriendo hasta llegar a lo que sería el mínimo valor del subárbol
      retorno = retorno->izq;
    }
  }
  else {
    // Si no tiene hijo izquierdo devolvemos directamente el nodo derecho
    retorno = nodo->der;
  }
  return retorno;
}



ITree itree_eliminar_r(ITree raiz, int inicio, int final){
  // Si raiz es NULL significa que el árbol (o subárbol) está vacío
  // y por lo tanto no hay qué eliminar
  if (raiz == NULL) {
    return raiz;
  }

  // Vemos si tenemos que ir por izquierda
  if (final < raiz->inte->inicio) {
    raiz->izq = itree_eliminar_r(raiz->izq, inicio, final);
  }
  // o por derecha
  else if (inicio > raiz->inte->fin) {
    raiz->der = itree_eliminar_r(raiz->der, inicio, final);
  }


  // Si estamos en el nodo a eliminar
  else if (raiz->izq == NULL || raiz->der == NULL) {
    // Si tiene hijo izquierdo tomaremos como temp al hijo izquierdo,
    // sino al derecho
    ITree temp = raiz->izq ? raiz->izq: raiz->der;

    // Si vemos que tampoco tiene hijo derecho, entonces estamos en el caso 
    // de una hoja y su eliminación es simple
    if (temp == NULL) {
      temp = raiz;
      raiz = NULL;
    }    
    // Si tenia un hijo
    else {
      *raiz = *temp;
    }
    free(temp->inte);
    free(temp);
    // Si hay algun rpoblema con memoria dsp ver que puede ser por no liberar el inte
  }
  else { 
    // Si no pasó lo anterior, estamos en el caso de un nodo con 2 hijos

    // Buscamos el minimo del subarbol derecho
    ITree temp = min_subarbol_derecho(raiz);

    // Este sera la nueva raiz asi que realizamos el cambio de valores
    raiz->inte->inicio = temp->inte->inicio;
    raiz->inte->fin = temp->inte->fin;
    // y lo "sacamos" de su posición eliminandolo
    raiz->der = itree_eliminar_r(raiz->der, temp->inte->inicio, temp->inte->fin); // va a ser caso sin hijos so rapido
  }
  
  if (raiz == NULL){
      return raiz;
  }
  // Si raiz no es NULL actualizamos la altura
  if (itree_altura(raiz->der) <= itree_altura(raiz->izq)) {
    raiz->alt = 1 + itree_altura(raiz->izq);
  }
  else{
    raiz->alt = 1 + itree_altura(raiz->izq);
  }

  // Balanceamos el árbol en caso de ser necesario
  int balance = itree_balance_factor(raiz);
  return hacer_avl(raiz, balance);
}

void itree_imprimir(ITree raiz) {
  if (raiz != NULL) {
    itree_imprimir(raiz->izq);
    if (raiz->inte->inicio == raiz->inte->fin) {
      printf("%d, ", raiz->inte->inicio); 
    }
    else {
      printf("%d:%d, ", raiz->inte->inicio, raiz->inte->fin);
    }
    itree_imprimir(raiz->der);
  }
}

void itree_recorrer_dfs(ITree raiz) {
  if (raiz != NULL) {
    // Se imprime la raiz
    printf ("[%d, %d]\n", raiz->inte->inicio, raiz->inte->fin);
    // Se vuelve a llamar a la función recursivamente para imprimir el subárbol izquierdo
    itree_recorrer_dfs(raiz->izq);
    // y luego el derecho
    itree_recorrer_dfs(raiz->der);
  }
} // Hecho con preorden

void itree_recorrer_bfs(ITree tree) {
  // Si no se trata de un árbol vacío
  if (tree != NULL) {
    // Armamos una lista con la raíz
    SList queue = slist_agregar_final(NULL, tree);

    // Mientras no hayamos vaciado la cola
    while (queue != NULL) {
      // Agregamos los hijos del primer elemento de la queue en caso de tenerlos
      if (((ITree)(queue->dato))->izq != NULL) {
        queue = slist_agregar_final(queue, ((ITree)(queue->dato))->izq);
      }
      if (((ITree)(queue->dato))->der != NULL) {
        queue = slist_agregar_final(queue, ((ITree)(queue->dato))->der);
      }

      // Lo imprimimos y luego lo eliminamos
      printf("[%d, %d]\n", ((ITree)(queue->dato))->inte->inicio, ((ITree)(queue->dato))->inte->fin);
      queue = slist_eliminar_inicio(queue);
    }
  }
}

