/*
 * Jerry.c
 *
 *  Created on: Nov 13, 2020
 *      Author: ise
 */

#include "Jerry.h"
#include "Defs.h"
Planet* Cr_p(char *name, float x, float y, float z)
{

	Planet* planet=(Planet*)malloc(sizeof(Planet));
	if(planet==NULL){
		printf("Error malloc planet \n");
		exit(0);}
	//memory for planet name
	planet->name=(char*)malloc((strlen(name)+1)*sizeof(char));
	if(planet->name==NULL){
		printf("Error malloc planet name \n");
		exit(0);}
	strcpy(planet->name,name);
	planet->x=x;
	planet->y=y;
	planet->z=z;
	return planet;
};

Origin* Cr_o(char *dim_name, Planet* planet)
{
	Origin* origin=(Origin*)malloc(sizeof(Origin));
	if(origin==NULL){
		printf("Error malloc origin \n");
		exit(0);}
	origin->dim_name=(char*)malloc((strlen(dim_name)+1)*sizeof(char));
	if(origin->dim_name==NULL){
		printf("Error malloc origin dim name \n");
		exit(0);}
	strcpy(origin->dim_name,dim_name);
	origin->planet = planet;
	return origin;
};

Pc* Cr_a(char *artname, float value)
{
	Pc* pc=(Pc*)malloc(sizeof(Pc));
	if(pc==NULL){
		printf("Error malloc pc \n");
		exit(0);}
	pc->name=(char*)malloc((strlen(artname)+1)*sizeof(char));
	if(pc->name==NULL){
		printf("Error malloc pc name \n");
		exit(0);}
	strcpy(pc->name,artname);
	pc->amount=value;
	pc->nextPcInJerry=NULL;
	pc->befor=NULL;
	pc->self=pc;
	return pc;
};

Jerry* Cr_j(char* ID, Origin* origin, int happy )
{
	Jerry* jerry=(Jerry*)malloc(sizeof(Jerry));
	if(jerry==NULL)
		exit(0);
	jerry->ID=(char*)malloc((strlen(ID)+1)*sizeof(char));
	if(jerry->ID==NULL)
		exit(0);
	strcpy(jerry->ID,ID);
	jerry->characterAmount=0;
	jerry->happines=happy;
	jerry->origin=origin;
	jerry->characterList =(Pc*) NULL;
	jerry->head=(Pc*) NULL;
	jerry->end=(Pc*)NULL;
	return jerry;
}




status printPlanet(Planet* planet)
{
	if(planet->name !=NULL)
	{
	printf("Planet : %s (%.2f,%.2f,%.2f) \n",planet->name,planet->x,planet->y,planet->z);
	return success;
	}
	else
		return failure;
}


status printJerry(Element elem)
{
if(elem ==NULL)
		return failure;
Jerry* jerry;
jerry=(Jerry*)elem;
printf("Jerry , ID - %s : \n",jerry->ID);
printf("Happiness level : %d \n",jerry->happines);
printf("Origin : %s \n",jerry->origin->dim_name);
printf("Planet : %s (%.2f,%.2f,%.2f) \n",jerry->origin->planet->name,jerry->origin->planet->x,jerry->origin->planet->y,jerry->origin->planet->z);
// print phyicial art

if (jerry->head!=NULL)
	{
	printf("Jerry's physical Characteristic available : \n");
	printf("\t");
	Pc* tmp=NULL;
	tmp= jerry->head;
	while(tmp->nextPcInJerry!=NULL)
	{
		printf("%s : %.2f", tmp->name,tmp->amount);
		printf(" , ");
		tmp=tmp->nextPcInJerry;
	}
	printf("%s : %.2f \n",jerry->end->name,jerry->end->amount );
	return success;
	}
}






//search function
Planet* searchplanet(char* name,Planet* arrp[],int size)
{
int i=0;
for(i= 0; i<size;i++)
	{
	if(strcmp(arrp[i]->name,name)==0)
				return arrp[i];
	}
	return NULL;
}


// function pc

bool isPcExist(Jerry* jerry, char* name)
{
	Pc* tmp=NULL;
	tmp=jerry->head;
	while(tmp!=NULL)
		{
		if(strcmp(tmp->name,name)==0)
			return true;
		tmp=tmp->nextPcInJerry;
		}

	return false;
}


Pc* PointerPcExist(Jerry* jerry, char* name)
{
	Pc* tmp=NULL;
		tmp=jerry->head;
		while(tmp!=NULL)
			{
			if(strcmp(tmp->name,name)==0)
				return tmp;
			tmp=tmp->nextPcInJerry;
			}
}



bool PlanetExist(Planet* arrp[], char* name , int pnum ,Planet* planet)
{
	Planet* pp=NULL;
	pp=searchplanet(name,arrp,pnum);
	if (pp==NULL){
		free(pp);
		return false;}
	else{planet=pp;
		pp=NULL;
		free(pp);
		return true;}
}




void AddPc(Jerry* jerry,Pc* pc)
{

	if(jerry->characterAmount==0)
	{
		jerry->characterList=pc;
		jerry->characterAmount++;
		jerry->head=jerry->characterList;
		jerry->end=jerry->characterList;
	}
	else
	{
		pc->befor=jerry->end;
		jerry->end->nextPcInJerry=pc;
		jerry->end=pc;
		jerry->characterAmount++;

	}
}


status DeletePc(Jerry* jerry, char* name)
{
	bool bool=isPcExist(jerry,name);
	if(bool==false)
		return failure;

	Pc* pcToDelete = PointerPcExist(jerry,name);
	Pc* check = jerry->head;
	if(check->name==pcToDelete->name)
	{
		jerry->head=pcToDelete->nextPcInJerry;
		jerry->characterAmount--;
		destroyPc(pcToDelete);
		return success;
	}
	if(jerry->end->name==pcToDelete->name)
	{
		Pc* tmp =NULL;
		tmp=jerry->end->befor;
		jerry->end=tmp;
		destroyPc(pcToDelete);
		jerry->end->nextPcInJerry=NULL;
		jerry->characterAmount--;
		return success;
	}

	while(check != NULL)
	{
		if(check->nextPcInJerry->name == pcToDelete->name)
		{
			check->nextPcInJerry=pcToDelete->nextPcInJerry;
			jerry->characterAmount--;
			destroyPc(pcToDelete);
			return success;
		}
		else {check=check->nextPcInJerry;}

	}
}



void updateJerryPc(Jerry* jerry,char* name)
{
	int i=0;
	bool bool = false;

	if (jerry->characterAmount==0)
	{
		jerry->characterList=NULL;
	}

	while(i<jerry->characterAmount && jerry->characterAmount>1)
	{

		if(strcmp(jerry->characterList[i].name,name)==0 && bool==false)
		{
			bool = true;
		}
		if(bool == true)
		{
			jerry->characterList[i] = jerry->characterList[i+1];
			//printf("%s \n",jerry->characterList[0].name);
		}
		i++;
	}

}

//destroy functions

void destroyPc(Pc* pc)
{
	free(pc->name);
	free(pc);


}

void destroyPcList(Jerry* jerry)
{
	if(jerry->characterList!=NULL){
	Pc* tmp=NULL;
	Pc* tmp2=NULL;
	tmp=jerry->head;
	tmp2=tmp->nextPcInJerry;

		while(tmp->nextPcInJerry!=NULL)
			{
			destroyPc(tmp);
			tmp=tmp2;
			tmp2=tmp->nextPcInJerry;
			}
		destroyPc(tmp);}

}


void destroyPlanet(Planet* planet)
{
	free(planet->name);
	free(planet);
}

void destroyPlanetList(Planet* arrp[],int pnum)
{
	int i = pnum-1;

	while(i>=0)
	{
		destroyPlanet(arrp[i]);
		i--;
	}
}

status destroyJerry(Element elem)
{
	if(elem ==NULL)
		return failure;
	Jerry* jerry;
	jerry=(Jerry*)elem;
	if(jerry->head!=NULL)
		destroyPcList(jerry);
	free(jerry->origin->dim_name);
	free(jerry->origin);
	free(jerry->ID);
	free(jerry);
	return success;
}


int* gethappines(Jerry* j)
{return &(j->happines);}


char* getid(Jerry* j)
{return j->ID;}

Element CopyId(Element elem)
{
if(elem==NULL)return NULL;
int j;
j=strlen((char*)elem)+1;
char* newID = (char*)malloc(j*sizeof(char));
strcpy(newID,(char*)elem);
return newID;
}

status(freeID)(Element elem)
{
char* p;
p=(char*)elem;
free(p);
return success;
}

status printID(Element elem)
{
if (elem==NULL)
		return failure;
char* p;
p=(char*)elem;
printf("%s \n",p);
return success;
}


Element CopyPJ(Element elem)
{
if(elem ==NULL)
	return NULL;
//Jerry* jp;
//*jp=*(Jerry*)elem;
//Jerry* JerryInHash;
//JerryInHash=(Jerry*)malloc(sizeof(struct Jerry_t));
//JerryInHash.ID=jp->ID;
//JerryInHash.characterAmount=jp->characterAmount;
//JerryInHash.characterList=jp->characterList;
//JerryInHash.end=jp->end;
//JerryInHash.happines=jp->happines;
//JerryInHash.head=jp->head;
//JerryInHash.origin=jp->origin;

return elem;
}


bool equalID(Element elem,Element elem2)
{
if(elem ==NULL)
	return false;
if(elem2 ==NULL)
	return false;
char* p = (char*)elem;
char* p2 = (char*)elem2;
if(strcmp(p,p2)==0)
	return true;
return false;
}

bool equalPointerJerry(Element elem,Element elem2)
{
	Jerry* j1;
	Jerry* j2;
	j1=(Jerry*)elem;
	j2=(Jerry*)elem2;

	if(equalID(j1->ID,j2->ID)==true)
		return true;
	return false;
}


int transformationIDToAskistring(Element elem)
{

    char* p = (char*)elem;
    int sum=0;
    int b;
    for(int i=0; i<strlen(p);i++){
        b=p[i];
        sum=sum+b;}
    return sum;
}

int transformationIDToAskiJerryId(Element elem)
{
Jerry* jerry;
jerry=(Jerry*)elem;
char* p = jerry->ID;
int sum=0;
int b;
for(int i=0; i<strlen(p);i++){
	b=p[i];
	sum=sum+b;}
return sum;
}

Pc* thisPcList(Element elem)
{
    Jerry* jp;
    jp=(Jerry*)elem;
    Pc* pclist;
    pclist=jp->head;
    return pclist;
}

Pc* nextPc(Element elem)
{
    Pc* next;
    next=(Pc*)elem;
    return next->nextPcInJerry;
}

char* PcName(Pc* pc)
{
    return pc->name;
}

char* getID(Element elem)
{
    Jerry* jp;
    jp=(Jerry*)elem;

    return jp->ID;

}

