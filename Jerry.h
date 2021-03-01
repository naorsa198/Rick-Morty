/*
 * Jerry.h
 *
 *  Created on: Nov 13, 2020
 *      Author: ise
 */
//#ifndef JERRY_H
//#define JERRY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
typedef struct PhysicalCharacteristics_t{

	char* name;
	float amount;
	struct PhysicalCharacteristics_t *nextPcInJerry;
	struct PhysicalCharacteristics_t *self;
	struct PhysicalCharacteristics_t *befor;


}Pc;

typedef struct planet_t{

	char* name;
	float x,y,z;
}Planet;

typedef struct Origin_t{

	char* dim_name;
	struct planet_t* planet; //pointer
}Origin;

typedef struct Jerry_t{

	char* ID;
	int happines;
	struct Origin_t* origin;
	int characterAmount;
	struct PhysicalCharacteristics_t *characterList;
	struct PhysicalCharacteristics_t *head;
	struct PhysicalCharacteristics_t *end;


}Jerry;



Jerry* Cr_j(char*,Origin*,int);
Planet* Cr_p(char*, float, float, float);
Pc* Cr_a(char*, float);
Origin* Cr_o(char*, Planet*);

enum e_bool isPcExist(Jerry*, char*);
enum e_bool PlanetExist(Planet* arrp[] , char* name, int pnum,Planet* planet);
Pc* PointerPcExist(Jerry* jerry, char* name);



void AddPc(Jerry*, struct PhysicalCharacteristics_t*);
enum e_status DeletePc(Jerry*, char*);
status printJerry(Element elem);
enum e_status printPlanet(Planet*);



void updateJerryPc(Jerry* jerry,char* name);


//search function
Planet* searchplanet(char* name, Planet* arrp[],int size);


//destroy function


void destroyPc(Pc* pc);
void destroyPcList(Jerry* jerry);

void destroyPlanet(Planet* planet);
void destroyPlanetList(Planet* arrp[],int);

status destroyJerry(Element elem);

char* getid(Jerry* j);
int* gethappines(Jerry* j);

Element CopyId(Element elem);
status freeID(Element elem);
Element CopyPJ(Element elem);
int transformationIDToAskiJerryId(Element elem);
int transformationIDToAskistring(Element elem);

bool equalID(Element elem,Element elem2);
status printID(Element elem);
bool equalPointerJerry(Element elem,Element elem2);
Pc* thisPcList(Element elem);

char* getID(Element elem);
Pc* thisPcList(Element elem);
Pc* nextPc(Element elem);
char* PcName(Pc* pc);

//#endif /* ifndef JERRY_H */
