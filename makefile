JerryBoree:HashTable.o Jerry.o KeyValuePair.o LinkedList.o MainFirst.o MultiValueHashTable.o
	gcc HashTable.o Jerry.o KeyValuePair.o LinkedList.o MainFirst.o MultiValueHashTable.o -o JerryBoree
MainFirst.o:MainFirst.c Jerry.h Defs.h MultiValueHashTable.h KeyValuePair.h LinkedList.h HashTable.h
	gcc -c MainFirst.c
LinkedList.o:LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
KeyValuePair.o:KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
HashTable.o:HashTable.c KeyValuePair.h Defs.h LinkedList.h HashTable.h Jerry.h
	gcc -c HashTable.c
MultiValueHashTable.o:MultiValueHashTable.c MultiValueHashTable.h Defs.h KeyValuePair.h LinkedList.h HashTable.h
	gcc -c MultiValueHashTable.c
Jerry.o:Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
clean: 
	rm -f *.o
