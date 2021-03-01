#ifndef _KeyValuePair_
#define _KeyValuePair_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

typedef struct KeyValuePair* KeyValuePair;

typedef void* ElementKey;
typedef void* ElementVal;
typedef void* DataElement;


typedef Element (*copyFunction)(Element);
typedef enum e_status (*freeFunction)(Element);
typedef char* (*Print)(Element);
typedef enum e_bool(*EqualFunction) (Element, Element);


KeyValuePair createKeyValuePair(copyFunction copyV,copyFunction copyK,
	freeFunction freeK,freeFunction freeV,Print lm_k,Print lm_v,EqualFunction cmp,ElementKey key, ElementVal val );

Element copyKv(Element kv); //to do



void destroyKeyValuePair(Element elem);
ElementKey getKey(KeyValuePair kv);
ElementVal getValue(KeyValuePair kv );
void displayKey(KeyValuePair kv);
void displayValue(KeyValuePair kv);
bool isEqualKey(KeyValuePair kv, ElementKey key);
bool isEqualvalue(KeyValuePair kv, ElementVal val);

void printKv(Element kv); //to do
bool Datafunc(KeyValuePair kv,DataElement data); //to do

void destroyKeyValuePairformulti(KeyValuePair kv);


#endif //_KeyValuePair_
