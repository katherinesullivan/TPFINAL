#ifndef __OPERACIONES_H__
#define __OPERACIONES_H__

#include <stddef.h>
#include "slist.h"
#include "conjunto.h"

ITree itree_union (ITree cjto1, ITree cjto2, int band);

ITree itree_comunes (ITree nodo, int inicio, int final, ITree cjto);

ITree itree_inter (ITree cjto1, ITree cjto2, ITree cjto3);



#endif /* __CONJUNTO_H__ */