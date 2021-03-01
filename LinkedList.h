#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct t_GenList* GenList;

typedef void* Element;
typedef void* DataElement;

typedef Element (*copyFunction)(Element);
typedef enum e_status (*freeFunction)(Element);
typedef enum e_status  (*printFunction)(Element);
typedef int (*isEqualFunction)(Element,Element);//1 true 0 false
typedef bool(*EqualFunction) (Element, Element);



GenList createLinkedList(copyFunction copyf, freeFunction freef, printFunction printfunc,EqualFunction isEqualKey);
status destroyInternalList(GenList list);   // destroy all the internal list in a list // destroy all the list values for a key
Element Copylist(Element kv);


void destroyList(GenList list);

status appendNode(GenList list, Element nodeData);
status deleteNode(GenList list, Element nodeData);
Element getDataByIndex(GenList list, int index);
void displayList(GenList list);


int getLengthList(GenList list);
Element searchByKeyInList(GenList list, DataElement data);

GenList GetInternalList(GenList,Element var);// return the list values of Key
status deleteNodeNoDeep(GenList list, Element nodeData);
#endif /* LINKEDLIST_H_ */
