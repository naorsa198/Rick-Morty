/*
 * MultiValueHashTable.h
 *
 *  Created on: Dec 5, 2020
 *      Author: ise
 */

#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "Defs.h"



typedef void* ElementKey;
typedef void* ElementVal;


typedef struct MultihashTable_s* MultihashTable;

typedef bool(*EqualFunction) (Element, Element);

MultihashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
		CopyFunction copyValue, FreeFunction freeValue, PrintFunction
		printValue, EqualFunction equalKey, TransformIntoNumberFunction
		transformIntoNumber, int hashNumber,EqualFunction equalVal  );

status destroyMultiValueHashTable(MultihashTable ms);

status addToMultiValueHashTable(MultihashTable ms, ElementKey key,ElementVal value);
Element lookupInMultiValueHashTable(MultihashTable ms, ElementKey key);
status removeFromMultiValueHashTable(MultihashTable ms, Element key, Element Value);
status displayMultiValueHashTable(MultihashTable ms, Element Key);
void removeEmpty(MultihashTable ms,Element elem);






#endif /* MULTIVALUEHASHTABLE_H_ */
