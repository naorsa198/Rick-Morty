/*
 * MultihashTable.c
 *
 *  Created on: Dec 5, 2020
 *      Author: ise
 */

#include "MultiValueHashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include "HashTable.h"
#define ALLOCATE(var,type,num)	\
	{if((var=(type*)malloc((num*sizeof(type))))==NULL)	\
{fprintf(stderr,"Memory Problem \n");exit(1);}}

struct MultihashTable_s
{
	hashTable MultiH;
	GenList ValList;
	GenList KeyList;
	EqualFunction cmpvalue;


};





MultihashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
		CopyFunction copyValue, FreeFunction freeValue, PrintFunction
		printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber,EqualFunction equalVal )
{
	MultihashTable ms;
	ALLOCATE(ms,struct MultihashTable_s,1);
	ms->MultiH=createHashTable( copyKey,  freeKey,  printKey, copyValue,freeValue,
						printValue,  equalKey,  transformIntoNumber,  hashNumber);

	ms->ValList= createLinkedList( copyValue, freeValue ,  printValue, equalVal);
	ms->KeyList=createLinkedList( copyKey, freeKey ,  printKey, equalKey);
	ms->cmpvalue=equalVal;

	return ms;

}



status destroyMultiValueHashTable(MultihashTable ms)
{
		if(ms==NULL)
			return failure;
		destroyHashTable(ms->MultiH);
		destroyList((ms->KeyList));
		destroyList((ms->ValList));
		free(ms);
		return success;
}


//status addToMultiValueHashTable(MultihashTable ms, ElementKey key,ElementVal value)
//{
//	GenList InsideList;
//	KeyValuePair kv;
//	kv=createKeyValuePair(ms->MultiH->copyValue,ms->MultiH->copyKey,ms->MultiH->freeKey,
//			ms->MultiH->freeValue,ms->MultiH->printKey,ms->MultiH->printValue,ms->MultiH->equalKey,key,value);

//	status check;
//	int k;
//	k=ms->MultiH->transformIntoNumber(key);
//	if(ms->MultiH->arrayGen[k]==0){
//		check=addToHashTable(ms->MultiH,key,value);}
//
//	else{InsideList=GetInternalList(ms->MultiH->arrayGen[k],key);
//			check=appendNode(InsideList,kv);}
//	destroyKeyValuePair(kv);
//	return check;
//
//}

status addToMultiValueHashTable(MultihashTable ms, ElementKey key,ElementVal value)
{
	if(ms ==NULL || key==NULL || value == NULL)
		return failure;
	GenList Vallist;
	ElementVal valuesForKey;
	valuesForKey= lookupInHashTable(ms->MultiH,key);
	if (valuesForKey==NULL){

		Vallist=Copylist(ms->ValList);
		appendNode(Vallist,value);
		addToHashTable(ms->MultiH,key,Vallist);
	}
	else {
		appendNode(valuesForKey,value);}
		return success;
}


Element lookupInMultiValueHashTable(MultihashTable ms, ElementKey key)
{
	GenList valuesForKey;
	valuesForKey= lookupInHashTable(ms->MultiH,key);
	if(valuesForKey==NULL)
		return NULL;
	return valuesForKey;
}

status removeFromMultiValueHashTable(MultihashTable ms, Element key, Element value)
{
	if(ms==NULL || key==NULL || value==NULL)
		return failure;

	status check;
	GenList valuesForKey;
	valuesForKey= lookupInHashTable(ms->MultiH,key);
	if(valuesForKey==NULL)
		return failure;
	if(getLengthList(valuesForKey)==1){
        deleteNodeNoDeep(valuesForKey,value);
	    check=removeFromHashTable(ms->MultiH,key);
		return check;}

    deleteNodeNoDeep(valuesForKey,value);
	return check;

}


status displayMultiValueHashTable(MultihashTable ms, Element key)
{
	if(ms==NULL)
		return failure;

	GenList valuesForKey;
	valuesForKey= lookupInHashTable(ms->MultiH,key);
	if(valuesForKey==NULL)
		return failure;
	displayList(valuesForKey);
	return success;
}



void removeEmpty(MultihashTable ms,Element elem)
{
    removeFromHashTable(ms->MultiH,elem);
}
