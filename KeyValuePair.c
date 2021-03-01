


#include "KeyValuePair.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#define ALLOCATE(var,type,num)	\
	{if((var=(type*)malloc((num*sizeof(type))))==NULL)	\
			{fprintf(stderr,"Memory Problem \n");exit(1);}}


struct KeyValuePair
{
	ElementVal val;
	ElementKey key;
	copyFunction copyV;
	copyFunction copyK;
	freeFunction freeK;
	freeFunction freeV;
	Print lm_k;
	Print lm_v;
	EqualFunction cmp;
	EqualFunction cmpvalue;
};




KeyValuePair createKeyValuePair(copyFunction copyV,copyFunction copyK, freeFunction freeK,freeFunction freeV
			,Print lm_k,Print lm_v,EqualFunction cmp,ElementKey key, ElementVal val )
{
	if(val==NULL || key== NULL)
	    return NULL;

    KeyValuePair kv;
	kv=(KeyValuePair)malloc(sizeof(struct KeyValuePair));
	if(kv==NULL)
	{fprintf(stderr,"Memory Problem \n");exit(1);}
    kv->cmpvalue=cmp;
    kv->cmp=cmp;
	kv->copyK=copyK;
	kv->copyV=copyV;
	kv->freeK=freeK;
	kv->freeV=freeV;
	kv->lm_k=lm_k;
	kv->lm_v=lm_v;
//	ALLOCATE(kv->val,ElementVal,1);
//	ALLOCATE(kv->key,ElementKey,1);
	kv->val= kv->copyV(val);
	kv->key=kv->copyK(key);
	return kv;
}

void destroyKeyValuePair(Element elem)
{
     KeyValuePair kv;
     kv=(KeyValuePair)elem;

	if(kv->key!=NULL)
		kv->freeK(kv->key);
	if(kv->val!=NULL)
		kv->freeV(kv->val);
	free(kv);
    kv=NULL;

}
void destroyKeyValuePairformulti(KeyValuePair kv)
{
    free(kv);
}

void displayKey(KeyValuePair kv)
{
	kv->lm_k(kv->key);
}

void displayValue(KeyValuePair kv)
{kv->lm_v(kv->val);}

ElementKey getKey(KeyValuePair kv)
{return kv->key;}

ElementVal getValue(KeyValuePair kv)
{return kv->val;}


bool isEqualKey(KeyValuePair kv, ElementKey key)
{
	bool check;
	check=kv->cmp(kv->key,key);
	if (check==true)
		return true;
	return false;
}



bool isEqualvalue(KeyValuePair kv, ElementVal val)
{
	bool check;
	check=kv->cmpvalue(kv->val,val);
			if(check==true)
				return true;
	return false;
}


Element copyKv(Element kv)
{
	if(kv ==NULL)
		return NULL;

//	KeyValuePair copyKv= (KeyValuePair)malloc(sizeof(struct KeyValuePair));
	KeyValuePair copyKvold;
	//if(copyKv==NULL)
	//	return NULL;
	copyKvold=(KeyValuePair)kv;
    KeyValuePair copyKv=copyKvold;

//	copyKv->cmp=copyKvold->cmp;
//	copyKv->cmpvalue=copyKvold->cmpvalue;
//	copyKv->copyK=copyKvold->copyK;
//	copyKv->copyV=copyKvold->copyV;
//	copyKv->freeK=copyKvold->freeK;
//	copyKv->freeV=copyKvold->freeV;
//	copyKv->key=copyKvold->key;
//	copyKv->val=copyKvold->val;
//	copyKv->lm_k=copyKvold->lm_k;
//	copyKv->lm_v=copyKvold->lm_v;
	return copyKv;
}


void printKv(Element kv) //to do
{
KeyValuePair newkv;
newkv=(KeyValuePair)kv;
newkv->lm_k(newkv->key);
newkv->lm_v(newkv->val);
}

bool Datafunc(KeyValuePair kv,DataElement data) //to do
{
	bool check;
	check=isEqualvalue(kv,(ElementKey)data);
	if(check==true){
		(KeyValuePair)data;
		data=kv;    //not sure its keep the pointer check it !
		return true;
	}
	bool check2;
	check2=isEqualvalue(kv,(ElementVal)data);
	if (check2==true){
		(KeyValuePair)data;
		data=kv;
		return true;
	}

	return false;


}

