/*
 * HashTable.c
 *
 *  Created on: Dec 4, 2020
 *      Author: ise
 */

#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include "HashTable.h"
#include "Jerry.h"
#define ALLOCATE(var,type,num)	\
	{if((var=(type*)malloc((num*sizeof(type))))==NULL)	\
{fprintf(stderr,"Memory Problem \n");exit(1);}}



struct hashTable_s
{
	CopyFunction copyKey;
	FreeFunction freeKey;
	PrintFunction printKey;
	CopyFunction copyValue;
	FreeFunction freeValue;
	PrintFunction printValue;
	EqualFunction equalKey;
	TransformIntoNumberFunction transformIntoNumber;
	int hashNumber;
	GenList* arrayGen;
};


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
		CopyFunction copyValue, FreeFunction freeValue, PrintFunction
		printValue, EqualFunction equalKey, TransformIntoNumberFunction
		transformIntoNumber, int hashNumber)

{
	hashTable hash;
	//ALLOCATE(hash,struct hashTable_s,1);
	hash=(struct hashTable_s*)malloc(sizeof(struct hashTable_s));
	if(hash==NULL)
		return NULL;
	hash->copyKey=copyKey;
	hash->copyValue=copyValue;
	hash->equalKey=equalKey;
	hash->freeKey=freeKey;
	hash->freeValue=freeValue;
	hash->hashNumber=hashNumber;
	hash->printKey=printKey;
	hash->printValue=printValue;
	hash->transformIntoNumber=transformIntoNumber;
    hash->arrayGen=(GenList*)malloc((hash->hashNumber)*sizeof(GenList));
    if(hash->arrayGen==NULL)
    {fprintf(stderr,"Memory Problem \n");exit(1);}

    return hash;
}


status destroyHashTable(hashTable hs)
{
	if(hs==NULL)
		return failure;
	int i;
	for(i=(hs->hashNumber-1);i>=0; i--){
	    if(hs->arrayGen[i]==NULL){
            destroyList(hs->arrayGen[i]);
            continue;}
		destroyList(hs->arrayGen[i]);
	}

	free(hs);
	return success;
}





status addToHashTable(hashTable hs, Element key,Element value)
{
	if(hs==NULL || key==NULL || value==NULL)
		return failure;

	if(lookupInHashTable(hs,key) !=NULL)
		return failure;
	GenList lol;
	int k;
	k= hs->transformIntoNumber(key);
	k=k%hs->hashNumber;
	KeyValuePair kv;
	kv=createKeyValuePair(hs->copyValue,hs->copyKey,hs->freeKey,hs->freeValue,hs->printKey,hs->printValue,hs->equalKey,key,value);
	if(hs->arrayGen[k]==NULL){
		lol=createLinkedList(copyKv,destroyKeyValuePair,printKv,isEqualKey);
		hs->arrayGen[k]=lol;
		appendNode(hs->arrayGen[k],kv);}
	else
		appendNode(hs->arrayGen[k],kv);

	return success;
}




Element lookupInHashTable(hashTable hs, Element key)  // to print or give back pointer ?
{
	if(hs==NULL || key==NULL)
		return NULL;
	int k;
	k=hs->transformIntoNumber(key);
	k=k%hs->hashNumber;

	if(hs->arrayGen[k]==NULL) //LO AMUR LEIKANES LEKAN...
		return NULL;
	KeyValuePair kv;
	kv=searchByKeyInList(hs->arrayGen[k],key);
		if(kv==NULL)
			return NULL;

	Element value;

	value=getValue(kv); //key= pointer of value beacuse getvalue return the pointer  to the value
	//Jerry* tmp;
	//tmp = (Jerry*)value;
	return value;
}






status removeFromHashTable(hashTable hs, Element key)
{
	int k;
	k= hs->transformIntoNumber(key);
	k=k%hs->hashNumber;
    deleteNode((hs->arrayGen[k]),(ElementKey)key);

	return success;
}


status displayHashElements(hashTable hs)  // need to create the print of first value and later key
{
	if (hs==NULL)
		return failure;
	int i;
	for(i=0; i<hs->hashNumber; i++){
		if(hs->arrayGen[i]==NULL)
			continue;
		displayList(hs->arrayGen[i]);
	}
	return success;
}










