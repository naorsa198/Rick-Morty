#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure } status;

typedef void * Element;
typedef void * Elementval;
typedef void * Elementkey;



typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);

//for create KeyValuePair



#endif /* DEFS_H_ */
