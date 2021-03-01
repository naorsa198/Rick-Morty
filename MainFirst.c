/*
 * MainFirst.c
 *
 *  Created on: Nov 13, 2020
 *      Author: ise
 */
#include <string.h>
#include <stdio.h>
#include "Jerry.h"
#include <ctype.h>

#include "MultiValueHashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include "HashTable.h"

//#define DEBUG




void PrintAllPlanets(Planet* planets[],int size)
 {
	 int counter=0;
	 while (counter<size)
	 {
		 printPlanet(planets[counter]);
		 printf(" \n");
		 counter++;
	 }
 }


status freeNathing(Element elem)
{
     return success;
}



static int jerrynum=0;
static int pcnum=0;
void jnumfunc(char* path){


			  //read text
			  FILE* f1 = fopen(path, "r");
			  if(f1 == NULL){

					printf("Error opening file");
					exit(0);
			  }

			  char ch=0; //!eof
			  int i=0;
			  char word[300] = "";

			  char planetName[300] = "";
			  char planetX[300] = "";
			  char planetY[300] = "";
			  char planetZ[300] = "";
			  int readingPLanets = 0; //0-fasle 1-planet name 2-X 3-Y 4-Z

			  char ID[300] = "";
			  char dimension[300] = "";
			  char planetNameJerry[300] = "";
			  char happinesLevel[300] = "";
			  int readingJerries = 0; //0-false 1-ID 2-dimension 3-planetNameJerry 4-happinesLevel 5-create Jerry 6-characteristics

			  char characteristic[300] = "";
			  char amount[300] = "";





			  while(ch != EOF){

				  ch = fgetc(f1);


				  if (strcmp(word, "Planets") == 0)
				  {
					  //ch = fgetc(f1); // \n
					  memset(word, 0, sizeof word); //clean word
					  i=0;
					  readingPLanets = 1;
				  }


				  if (strcmp(word, "Jerries") == 0)
				  {
					  //ch = fgetc(f1); // \n
					  memset(word, 0, sizeof word); //clean word
					  readingPLanets = 0;
					  readingJerries = 1; //start reading jerries
					  i=0;
				  }

				  //reading planets

				  if (ch == ',' && readingPLanets == 1) // read name
				  {
					  strcat(planetName,word);
					  readingPLanets = 2;
					  memset(word, 0, sizeof word); //clean word
					  i=0;
				  }


				  else if (ch == ',' && readingPLanets == 2) // read X
				  {

					  strcat(planetX,word);
					  readingPLanets = 3;
					  memset(word, 0, sizeof word); //clean word
					  i=0;
				  }

				  else if (ch == ',' && readingPLanets == 3) // read Y
				  {

					  strcat(planetY,word);
					  readingPLanets = 4;
					  memset(word, 0, sizeof word); //clean word
					  i=0;
				  }

				  else if (ch == '\n' && readingPLanets == 4) // read Z
				  {

					  strcat(planetZ,word);
					  readingPLanets = 5;
					  memset(word, 0, sizeof word); //clean word
					  i=0;
					  //ch = fgetc(f1);//end line /n next planet
				  }

				  else if (readingPLanets == 5)
				  {



					  memset(planetName, 0, sizeof planetName); //clean word
					  memset(planetX, 0, sizeof planetX); //clean word
					  memset(planetY, 0, sizeof planetY); //clean word
					  memset(planetZ, 0, sizeof planetZ); //clean word

					  readingPLanets = 1;

				  }

				  //reading jerries

				  if (ch == ',' && readingJerries == 1) // read name
				  {
				  	strcat(ID,word);
				  	readingJerries = 2;
				  	memset(word, 0, sizeof word); //clean word
				  	i=0;
				  }


				  else if (ch == ',' && readingJerries == 2) // read dimension
				  {

				  	strcat(dimension,word);
				  	readingJerries = 3;
				  	memset(word, 0, sizeof word); //clean word
				  	i=0;
				  }

				  else if (ch == ',' && readingJerries == 3) // read planetNameJerry
				  {

				  	strcat(planetNameJerry,word);
				  	readingJerries = 4;
				  	memset(word, 0, sizeof word); //clean word
				  	i=0;
				  }

				  else if (ch == '\n' && readingJerries == 4) // read happinesLevel
				  {

				  	strcat(happinesLevel,word);
				  	readingJerries = 5;
				  	memset(word, 0, sizeof word); //clean word
				  	i=0;
				  	//ch = fgetc(f1);//end line
				  }

				  else if (readingJerries == 5)
				  {


					jerrynum=jerrynum+1;


					memset(ID, 0, sizeof ID); //clean word
					memset(dimension, 0, sizeof dimension); //clean word
					memset(planetNameJerry, 0, sizeof planetNameJerry); //clean word
					memset(happinesLevel, 0, sizeof happinesLevel); //clean word



					readingJerries = 6;


				  }

				  else if (readingJerries == 6) //create characteristics for Jerry
				  {


					  if(ch == ':')
					  {
						  strcat(characteristic,word);
						  memset(word, 0, sizeof word); //clean word
						  i=0;
					  }

					  else if (ch == ',') // previous jerry with no charactitics
					  {
						  strcat(ID,word);
						  readingJerries = 2;
						  memset(word, 0, sizeof word); //clean word
						  i=0;
					  }

					  else if(ch == '\n')
					  {
						  strcat(amount,word);
						  memset(word, 0, sizeof word); //clean word
						  //ch = fgetc(f1);//end line /n
						  i=0;

						 // printf("%s\n",characteristic);
						  //printf("%s\n", amount);

						pcnum=pcnum+1;

						  memset(amount, 0, sizeof amount);
						  memset(characteristic, 0, sizeof characteristic);

					  }

				  }

				  word[i] = ch;
				  i++;


				  if(word[0] == ',' || word[0] ==  '\t' || word[0] ==  ':' || word[0] ==  '\n' || word[0] ==  '\r') //remove
				  {
					  memset(word, 0, sizeof word); //clean word
					  i=0;
				  }
			  }

}




int main(int argc, char* argv[]) {

    int pnum = atoi(argv[1]);
    int jnum=0;
    Planet *planets[pnum];

    jnumfunc(argv[2]);
    jerrynum=jerrynum*3;
    hashTable JerryHash;
    JerryHash = createHashTable(CopyId, freeID, printID,
                                CopyPJ, destroyJerry, printJerry, equalID, transformationIDToAskistring, jerrynum);


    MultihashTable MsCp;
    MsCp = createMultiValueHashTable(CopyId, freeID, printID,
                                     CopyPJ, freeNathing, printJerry, equalID, transformationIDToAskistring, jerrynum,
                                     equalPointerJerry);


    int planetIndex = 0;



    GenList JerryInOrder;
    JerryInOrder=createLinkedList(CopyPJ,freeNathing,printJerry,equalPointerJerry);

    //read text
    FILE *f1 = fopen(argv[2], "r");
#ifdef DEBUG

    if (f1 == NULL) {

        printf("Error opening file");
        exit(0);
    }
#endif
    char ch = 0; //!eof
    int i = 0;
    char word[300] = "";

    char planetName[300] = "";
    char planetX[300] = "";
    char planetY[300] = "";
    char planetZ[300] = "";
    int readingPLanets = 0; //0-fasle 1-planet name 2-X 3-Y 4-Z

    char ID[300] = "";
    char dimension[300] = "";
    char planetNameJerry[300] = "";
    char happinesLevel[300] = "";
    int readingJerries = 0; //0-false 1-ID 2-dimension 3-planetNameJerry 4-happinesLevel 5-create Jerry 6-characteristics

    char characteristic[300] = "";
    char amount[300] = "";

    Jerry *jp;


    while (ch != EOF) {
        ch = fgetc(f1);


        if (strcmp(word, "Planets") == 0) {
            //ch = fgetc(f1); // \n
            memset(word, 0, sizeof word); //clean word
            i = 0;
            readingPLanets = 1;
        }


        if (strcmp(word, "Jerries") == 0) {
            //ch = fgetc(f1); // \n
            memset(word, 0, sizeof word); //clean word
            readingPLanets = 0;
            readingJerries = 1; //start reading jerries
            i = 0;
        }

        //reading planets

        if (ch == ',' && readingPLanets == 1) // read name
        {
            strcat(planetName, word);
            readingPLanets = 2;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == ',' && readingPLanets == 2) // read X
        {

            strcat(planetX, word);
            readingPLanets = 3;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == ',' && readingPLanets == 3) // read Y
        {

            strcat(planetY, word);
            readingPLanets = 4;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == '\n' && readingPLanets == 4) // read Z
        {

            strcat(planetZ, word);
            readingPLanets = 5;
            memset(word, 0, sizeof word); //clean word
            i = 0;
            //ch = fgetc(f1);//end line /n next planet
        } else if (readingPLanets == 5) {
            float x = atof(planetX);
            float y = atof(planetY);
            float z = atof(planetZ);

            planets[planetIndex] = Cr_p(planetName, x, y, z);
            planetIndex++;


            memset(planetName, 0, sizeof planetName); //clean word
            memset(planetX, 0, sizeof planetX); //clean word
            memset(planetY, 0, sizeof planetY); //clean word
            memset(planetZ, 0, sizeof planetZ); //clean word

            readingPLanets = 1;

        }

        //reading jerries

        if (ch == ',' && readingJerries == 1) // read name
        {
            strcat(ID, word);
            readingJerries = 2;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == ',' && readingJerries == 2) // read dimension
        {

            strcat(dimension, word);
            readingJerries = 3;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == ',' && readingJerries == 3) // read planetNameJerry
        {

            strcat(planetNameJerry, word);
            readingJerries = 4;
            memset(word, 0, sizeof word); //clean word
            i = 0;
        } else if (ch == '\n' && readingJerries == 4) // read happinesLevel
        {

            strcat(happinesLevel, word);
            readingJerries = 5;
            memset(word, 0, sizeof word); //clean word
            i = 0;
            //ch = fgetc(f1);//end line
        } else if (readingJerries == 5) {

            Planet *tempPlanet = NULL;
            tempPlanet = searchplanet(planetNameJerry, planets, pnum);
            Origin *currentOrigin = NULL;
            currentOrigin = Cr_o(dimension, tempPlanet);

            int happyCurrent = atoi(happinesLevel);

            jp = Cr_j(ID, currentOrigin,
                      happyCurrent);    //call create Jerry func here Cr_j(CurrentOrigin,ID,happinessLevel,)
            addToHashTable(JerryHash, jp->ID, jp);
            appendNode(JerryInOrder,jp);

            jnum++;
            memset(ID, 0, sizeof ID); //clean word
            memset(dimension, 0, sizeof dimension); //clean word
            memset(planetNameJerry, 0, sizeof planetNameJerry); //clean word
            memset(happinesLevel, 0, sizeof happinesLevel); //clean word



            readingJerries = 6;


        } else if (readingJerries == 6) //create characteristics for Jerry
        {


            if (ch == ':') {
                strcat(characteristic, word);
                memset(word, 0, sizeof word); //clean word
                i = 0;
            } else if (ch == ',') // previous jerry with no charactitics
            {
                strcat(ID, word);
                readingJerries = 2;
                memset(word, 0, sizeof word); //clean word
                i = 0;
            } else if (ch == '\n') {
                strcat(amount, word);
                memset(word, 0, sizeof word); //clean word
                //ch = fgetc(f1);//end line /n
                i = 0;

//					  printf("%s\n",characteristic);
//					  printf("%s\n", amount);

                float amountfloat = atof(amount);
                struct PhysicalCharacteristics_t *currentArtibute = NULL;
                currentArtibute = Cr_a(characteristic, amountfloat);

                //Element elem;
                //elem=lookupInHashTable(JerryHash, jp->ID);
                //jp=(Jerry*)elem;
                AddPc(jp, currentArtibute);

          //      addToHashTable(PcHash, jp->ID, currentArtibute->name);
                char* MultiPc;
                MultiPc=(char*)malloc((strlen(currentArtibute->name)+1)*sizeof(char));
                strcpy(MultiPc,currentArtibute->name);
//				KeyValuePair PcJp;
//				PcJp=createKeyValuePair(CopyPJ,CopyId,freeNathing,freeID,printJerry,printID,equalPointerJerry,jp,amount);

                addToMultiValueHashTable(MsCp,MultiPc,jp);



            //    printJerry(jp);
                memset(amount, 0, sizeof amount);
                memset(characteristic, 0, sizeof characteristic);

            }

        }

        word[i] = ch;
        i++;


        if (word[0] == ',' || word[0] == '\t' || word[0] == ':' || word[0] == '\n' || word[0] == '\r') //remove
        {
            memset(word, 0, sizeof word); //clean word
            i = 0;
        }
    }



    char userID[300];
    char userplanet[300];
    char UserDim[300];
    char UserHappy[300];
    char Pc[300];

    status case1(hashTable hs, Planet *planets[], int pnum,GenList JerryInOrder) {
        printf("What is your Jerry's ID ? \n");
        scanf("%s", userID);
        Element elem;
        bool checkPc;
        elem = lookupInHashTable(hs, userID);
        if (elem != NULL) {
            printf("Rick did you forgot ? you already left him here ! \n");
            memset(userID, 0, sizeof userID);
            return failure;
        }
        printf("What planet is your Jerry from ? \n");
        scanf("%s", userplanet);
        Planet* planet;
        checkPc = PlanetExist(planets, userplanet, pnum,planet);
        if (checkPc == false) {
            printf("%s is not a known planet ! \n",userplanet);
            memset(userplanet, 0, sizeof userplanet);
            return failure;
        }

        printf("What is your Jerry's dimension ? \n");
        scanf("%s", UserDim);
        printf("How happy is your Jerry now ? \n");
        scanf("%s", UserHappy);
        int happyCurrent = atoi(UserHappy);
        Planet* p = searchplanet(userplanet, planets, pnum);
        Origin* newOrigin;
        newOrigin = Cr_o(UserDim,p);
        Jerry* newJerry;
        newJerry = Cr_j(userID, newOrigin, happyCurrent);
        addToHashTable(hs, userID, newJerry);
        printJerry(newJerry);
        appendNode(JerryInOrder,newJerry);
        memset(userplanet, 0, sizeof userplanet);
        memset(UserDim, 0, sizeof UserDim);
        memset(UserHappy, 0, sizeof UserHappy);
        memset(userID, 0, sizeof userID);
        jnum++;
        return success;
    }


    status case2(hashTable jhs,MultihashTable MsCp) {
    	printf("What is your Jerry's ID ? \n");
    	scanf("%s", userID);
    	Element elem;
    	elem = lookupInHashTable(jhs,userID);
    	if (elem == NULL) {
    	    printf("Rick this Jerry is not in the daycare ! \n");
    	    memset(userID, 0, sizeof userID);
    	    return failure;
    	}
    	printf("What physical characteristic can you add to Jerry - %s ? \n",userID);
    	scanf("%s", Pc);
    	elem = lookupInMultiValueHashTable(MsCp,Pc);
    	Element check;
		Element tmpj;
		tmpj = lookupInHashTable(jhs,userID);

    	check = searchByKeyInList(elem, tmpj);
    	if(check!=NULL){
    		printf("The information about his %s already available to the daycare ! \n",Pc);
            memset(userID, 0, sizeof Pc);
            memset(userID, 0, sizeof userID);
            return failure;}//pc already exist for given jerry
    	printf("What is the value of his %s ? \n",Pc);
    	scanf("%s", amount);
    	float amountfloat = atof(amount);
    	elem = lookupInHashTable(jhs,userID);
    	Jerry* jp;
    	jp=(Jerry*)elem;
    	struct PhysicalCharacteristics_t* tmpPc =NULL;
    	tmpPc = Cr_a(Pc, amountfloat);
    	AddPc(elem,tmpPc); // elem = jerry pointer ? or need to do casting ?
//    	KeyValuePair PcJp;
//        PcJp=createKeyValuePair(CopyPJ,CopyId,freeNathing,freeID,printJerry,printID,equalPointerJerry,jp,amount);
        char* MultiPc;
        MultiPc=(char*)malloc((strlen(Pc)+1)*sizeof(char));
        if(MultiPc==NULL)
        	exit(0);
        strcpy(MultiPc,Pc);
		addToMultiValueHashTable(MsCp,MultiPc,jp);// multihash,pc name,jerry id
    	printf("%s :\n",Pc);
		displayMultiValueHashTable(MsCp,Pc);
        memset(Pc, 0, sizeof Pc);
        memset(UserDim, 0, sizeof UserDim);
        memset(amount, 0, sizeof amount);
        memset(userID, 0, sizeof userID);
        return success;
    }
    //case1(JerryHash,planets,pnum);

    status case3(hashTable jhs,MultihashTable MsCp) {
        printf("What is your Jerry's ID ? \n");
        scanf("%s", userID);
        Element elem;
        elem = lookupInHashTable(jhs,userID); //RETURN POINTER JERRY
        if (elem == NULL) {
            printf("Rick this Jerry is not in the daycare ! \n");
            memset(userID, 0, sizeof userID);
            return failure;
        }
        printf("What physical characteristic do you want to remove from Jerry - %s ? \n",userID);
        scanf("%s", Pc);

        elem = lookupInMultiValueHashTable(MsCp,Pc);//return list of jerris-id
        Element check;
        Element tmpj;
        tmpj = lookupInHashTable(jhs,userID); //RETURN POINTER JERRY
        check = searchByKeyInList(elem, tmpj);
        if(check==NULL){
            printf("The information about his %s doesnt available to the daycare ! \n",Pc);
            memset(Pc, 0, sizeof Pc);
            memset(userID, 0, sizeof userID);
            return failure;}//pc dont exist for given jerry

        deleteNodeNoDeep(elem,tmpj);

        if(getLengthList(elem)==0)
            removeEmpty(MsCp,Pc);
        DeletePc(tmpj,Pc);
        printJerry(tmpj);

        memset(Pc, 0, sizeof Pc);
        memset(userID, 0, sizeof userID);
        return success;
    }

    status case4(hashTable jhs,MultihashTable MsCp,GenList JerryInOrder)
     {

        printf("What is your Jerry's ID ? \n");
        scanf("%s", userID);
        Element elem;
        elem = lookupInHashTable(jhs, userID);
        if (elem == NULL) {
            printf("Rick this Jerry is not in the daycare ! \n");
            memset(userID, 0, sizeof userID);
            return failure;}
        Jerry* jerry;
        jerry=(Jerry*)elem;
        struct PhysicalCharacteristics_t* pcinjerry;
        pcinjerry=thisPcList(elem);
        while(pcinjerry!=NULL)
        {
            char* namepc;
            namepc=PcName(pcinjerry);
            removeFromMultiValueHashTable(MsCp,namepc,jerry);
            pcinjerry=nextPc(pcinjerry);
        }
        char* id;
        id=getid(jerry);
        deleteNodeNoDeep(JerryInOrder,jerry);
        removeFromHashTable(jhs,id);
        printf("Rick thank for using our daycare service ! Your Jerry awaits ! \n");
        memset(userID, 0, sizeof userID);
        jnum--;
        return success;
    }

    status case5(MultihashTable MsCp,GenList JerryInOrder,hashTable jhs)
    {

        printf("What do you remember about your Jerry ? \n");
        scanf("%s", Pc);
        Element elem;
        elem = lookupInMultiValueHashTable(MsCp,Pc);//return list of jerris
        if(elem==NULL){
    	   printf("Rick we can not help you - we do not know any Jerry's %s ! \n",Pc);
    	   return failure;}

        char* userValue[300];
        printf("What do you remember about the value of his %s ? \n",Pc);
        scanf("%s", userValue);
        float userValueFloat = atof(userValue);

        GenList list;
        list = (GenList)elem;
        float min;
        float DataFloat;
        struct PhysicalCharacteristics_t* PcPointer;
        Jerry* jerry = getDataByIndex(list, 0);
        PcPointer=PointerPcExist(jerry,Pc);
        DataFloat=PcPointer->amount;

        int saveJerryIndex = 0;

        if(DataFloat>userValueFloat)
        	min = DataFloat - userValueFloat;
        else
        	min = userValueFloat - DataFloat;

        float tempMin;
        for(i=1;i<getLengthList(list);i++)
        {
            jerry = getDataByIndex(list, i);
            PcPointer=PointerPcExist(jerry,Pc);
            DataFloat=PcPointer->amount;

            if(DataFloat>userValueFloat)
            	tempMin = DataFloat - userValueFloat;
            else
            	tempMin = userValueFloat - DataFloat;
            if(tempMin<min){
            	min=tempMin;
            	saveJerryIndex = i;}
        		//printf("%f\n",min);
        }
        Element JerryElem;
        JerryElem=getDataByIndex(list, saveJerryIndex);
        char *jerryid;
        struct PhysicalCharacteristics_t *pcinjerry;
        pcinjerry = thisPcList(JerryElem);
        JerryElem = (Jerry*)JerryElem;
        jerryid = getid(JerryElem);

        printf("Rick this is the most suitable Jerry we found : \n");
        printJerry(JerryElem);
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
        while (pcinjerry != NULL) {
            char *namepc;
            namepc = PcName(pcinjerry);
            removeFromMultiValueHashTable(MsCp, namepc, JerryElem);
            pcinjerry = nextPc(pcinjerry);
        }
        deleteNodeNoDeep(JerryInOrder, JerryElem);
        removeFromHashTable(jhs, jerryid);
        return success;
    }


    status case6(hashTable jhs, MultihashTable MsCp,GenList JerryInOrder) {
        int size;
        size=getLengthList(JerryInOrder);
        if(size==0){
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return failure;}
        Element elem;
        Jerry* minJerry;
        int minHappy;

        printf("Rick this is the most suitable Jerry we found : \n");
        elem = getDataByIndex(JerryInOrder, 0);
        Jerry* jerry2;
        jerry2 = (Jerry*) elem;
        minJerry=jerry2;
        int happiness;
        minHappy = *(gethappines(jerry2));
        int i = 0;
        i = (getLengthList(JerryInOrder));
        int j;
        for (j = 0; j < i; j++) {
            elem = getDataByIndex(JerryInOrder, j);
            Jerry *jerry3;
            jerry3 = (Jerry *) elem;
            happiness = *(gethappines(jerry3));
            if (minHappy - happiness > 0) {
                minHappy = happiness;
                minJerry = jerry3;
            }
        }
        printJerry(minJerry);
        //deleiting jerry

        Jerry *jerry;
        jerry = (Jerry*) minJerry;
        struct PhysicalCharacteristics_t *pcinjerry;
        pcinjerry = thisPcList(minJerry);
        while (pcinjerry != NULL) {
            char *namepc;
            namepc = PcName(pcinjerry);
            removeFromMultiValueHashTable(MsCp, namepc, jerry);
            pcinjerry = nextPc(pcinjerry);
        }
        char *jerryid;
        jerryid = getid(jerry);

        deleteNodeNoDeep(JerryInOrder, jerry);
        removeFromHashTable(jhs, jerryid);
        printf("Rick thank for using our daycare service ! Your Jerry awaits ! \n");
        jnum=jnum-1;
        return success;
    }


    status case7_1(GenList JerryInOrder)
    {
        int size;
        size=getLengthList(JerryInOrder);
        if(size==0){
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
            return failure;}
        displayList(JerryInOrder);
        return success;
    }

    status case7_2(MultihashTable MsCp,GenList JerryInOrder)
    {
        int size;
        size=getLengthList(JerryInOrder);
        if(size==0){
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
            return failure;}


        Element elem;
        printf("What physical characteristic ? \n");
        scanf("%s", Pc);
        elem = lookupInMultiValueHashTable(MsCp,Pc);//return list of jerris-id
       if(elem==NULL){
           printf("Rick we can not help you - we dont know any Jerry's %s ! \n",Pc);
           memset(userID, 0, sizeof Pc);
           return failure;}
      //RETURN POINTER JERRY
             displayList(elem);
        memset(userID, 0, sizeof Pc);
        return success;//pc dont exist for given jerry
    }


    status case7_3(Planet* arrp[],int pnum)
    {
        int i;
        for (i=0;i<pnum;i++)
            printPlanet(arrp[i]);
        return success;
    }

    status case8_1(GenList JerryInOrder) {
        Element elem;
        int i;
        int j;
        Jerry* jerry;
        j=getLengthList(JerryInOrder);
        if(j==0)
        	return failure;
        for(i=0;i<j;i++){
            elem=getDataByIndex(JerryInOrder,i);
                    jerry=(Jerry*)elem;

            if (*(gethappines(jerry))>= 20 && *(gethappines(jerry)) <= 85) {
                int* a=gethappines(jerry);
                *a=*a+15;
                continue;
            }
            if (*(gethappines(jerry)) > 85) {
                int* a=gethappines(jerry);
                *a=100;
                continue;

            }
            if (*(gethappines(jerry)) <= 19 && *(gethappines(jerry)) >= 5) {
                int* a=gethappines(jerry);
                *a=*a-5;
                continue;

            }
            if (*(gethappines(jerry)) < 5) {
                int* a=gethappines(jerry);
                *a=0;
                continue;

            }
        }
        printf("The activity is now over ! \n");
        displayList(JerryInOrder);

        return success;
    }


    status case8_2(GenList JerryInOrder) {



        Element elem;
        int i;
        int j;
        Jerry* jerry;
        j=getLengthList(JerryInOrder);
        if(j==0){
            return failure;}
        for(i=0;i<j;i++){
            elem=getDataByIndex(JerryInOrder,i);
            jerry=(Jerry*)elem;

            if (*(gethappines(jerry))>= 50 && *(gethappines(jerry)) <= 90) {
                int* a=gethappines(jerry);
                *a=*a+10;
                continue;
            }
            if (*(gethappines(jerry)) > 90) {
                int* a=gethappines(jerry);
                *a=100;
                continue;

            }
            if (*(gethappines(jerry)) <= 49 && *(gethappines(jerry)) >= 10) {
                int* a=gethappines(jerry);
                *a=*a-10;
                continue;

            }
            if (*(gethappines(jerry)) < 10) {
                int* a=gethappines(jerry);
                *a=0;
                continue;

            }
        }
        printf("The activity is now over ! \n");
        displayList(JerryInOrder);

        return success;
    }


    status case8_3(GenList JerryInOrder) {
        Element elem;
        int i;
        int j;
        Jerry* jerry;
        j=getLengthList(JerryInOrder);
        for(i=0;i<j;i++){
            elem=getDataByIndex(JerryInOrder,i);
            jerry=(Jerry*)elem;

            if (*(gethappines(jerry))>= 80 ) {
                int* a=gethappines(jerry);
                *a=100;}
            else
            {  int* a=gethappines(jerry);
                *a=*a+20;}
        }
        printf("The activity is now over ! \n");
        displayList(JerryInOrder);

        return success;
    }


    status case9(GenList JerryInOrder,hashTable JerryHash, MultihashTable MsCp, Planet* planets[])
    {
        destroyList(JerryInOrder);
        destroyMultiValueHashTable(MsCp);
        destroyHashTable(JerryHash);
        destroyPlanetList(planets,pnum);
        return success;
    }
#ifdef DEBUG
  //case1(JerryHash,planets,pnum,JerryInOrder);
    //case2(JerryHash,MsCp);
  //  case3(JerryHash,MsCp);
   // case4(JerryHash,MsCp,sadness,JerryInOrder);
   // printf("test 6 @@@@@@@@@@@@@@@ : \n");
  //  displayHashElements(JerryHash);
    //printf("\n\n\n");
  //  case6(jnum,JerryHash,MsCp,JerryInOrder);

   // case7_1(JerryInOrder,jnum);
  //  case7_2(MsCp);
   // case8_1(happyarray,JerryInOrder);
   //  case8_3(JerryInOrder);

   // printf("\n\n\n");
     //printf("test @@@@@@@@@@@@@@@ : \n");
  //   displayList(JerryInOrder);
//    char* pc ="LimbsNumber";
//    displayMultiValueHashTable(MsCp,pc);
 //   displayHashElements(JerryHash);
//    destroyHashTable(JerryHash);
 //   destroyPlanetList(planets,pnum);
   //destroyList(JerryInOrder);


#endif


            int size;
            char tmp3[300];
            int flag3;
            char tmp2[300];
            int flag2;
		  	int flag;
		  	char tmp[300];
		    while( flag != 9 ) {
            printf("Welcome Rick, what are your Jerry's needs today ? \n");
            printf("1 : Take this Jerry away from me \n");
            printf("2 : I think I remember something about my Jerry \n");
            printf("3 : Oh wait. That can't be right \n");
            printf("4 : I guess I will take back my Jerry now \n");
            printf("5 : I can't find my Jerry. Just give me a similar one \n");
            printf("6 : I lost a bet. Give me your saddest Jerry \n");
            printf("7 : Show me what you got \n");
            printf("8 : Let the Jerries play \n");
            printf("9 : I had enough. Close this place \n");
            scanf("%s",tmp);

		      		if (strlen(tmp)!=1){
					memset(word, 0, sizeof tmp); //clean word
		      		flag=11;
		      		}
                if (strcmp(tmp, "0") == 0)
                        flag = 0;
		      		if (strcmp(tmp, "1") == 0) {
		      			flag = 1;
		      		} else if (strcmp(tmp, "2") == 0) {
		      			flag = 2;
		      		} else if (strcmp(tmp, "3") == 0)
		      			flag = 3;
		      		else if (strcmp(tmp, "4") == 0)
		      			flag = 4;
		      		else if (strcmp(tmp, "5") == 0)
		      			flag = 5;
		      		else if (strcmp(tmp, "6") == 0)
		      			flag = 6;
		      		else if (strcmp(tmp, "7") == 0)
		      			flag = 7;
                    else if (strcmp(tmp, "8") == 0)
                         flag = 8;
                    else if (strcmp(tmp, "9") == 0)
                         flag = 9;

		      switch( flag ) {
                          case 1:  /*add jerry */
                              case1(JerryHash,planets,pnum,JerryInOrder);
                              memset(word, 0, sizeof tmp);
                              break;


		                case 2: //add pc to jerry
                            case2(JerryHash,MsCp);
                            memset(word, 0, sizeof tmp);
		                		break;
//
		                case 3: //delet pc from jerry
                                case3(JerryHash,MsCp);
				      			memset(word, 0, sizeof tmp);

		                		break;

		                case 4: //delete jerry
                                  case4(JerryHash,MsCp,JerryInOrder);
                                  memset(word, 0, sizeof tmp);
		                    	 	break;
//
//
		                case 5: //the simiilar jerry
                             case5( MsCp, JerryInOrder, JerryHash);
                                memset(word, 0, sizeof tmp);

						    		break;
//
//
//
		                case 6://take sadness
                            case6(JerryHash,MsCp,JerryInOrder);
                            memset(word, 0, sizeof tmp);
								break;


//   //  case8_3(JerryInOrder);
//

                        case 7:
                                  printf("What information do you want to know ? \n");
                                  printf("1 : All Jerries \n");
                                  printf("2 : All Jerries by physical characteristics \n");
                                  printf("3 : All known planets \n");
                                  scanf("%s",tmp2);
                                      if (strlen(tmp2)!=1){
                                          memset(word, 0, sizeof tmp); //clean word
                                          memset(word, 0, sizeof tmp2); //clean word
                                          flag2=0;
                                      }

                                      if (strcmp(tmp2, "1") == 0) {
                                          flag2 = 1;
                                      } else if (strcmp(tmp2, "2") == 0) {
                                          flag2 = 2;
                                      } else if (strcmp(tmp2, "3") == 0)
                                          flag2 = 3;
                                      switch( flag2 ) {
                                          case 1 :   case7_1(JerryInOrder);
                                              memset(word, 0, sizeof tmp); //clean word
                                              memset(word, 0, sizeof tmp2); //clean word
                                                      break;


                                          case 2:     case7_2(MsCp,JerryInOrder);
                                              memset(word, 0, sizeof tmp); //clean word
                                              memset(word, 0, sizeof tmp2); //clean word
                                                      break;

                                          case 3:       case7_3(planets,pnum);
                                              memset(word, 0, sizeof tmp); //clean word
                                              memset(word, 0, sizeof tmp2); //clean word
                                                        break;

                                          default: printf("Rick this option is not known to the daycare ! \n");
                                              memset(word, 0, sizeof tmp); //clean word
                                              memset(word, 0, sizeof tmp2); //clean word
                                                    break;}
                                                    break;

                        case 8:

                                 size=getLengthList(JerryInOrder);
                                 if(size==0){
                                          printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                            break;}

                                    printf("What activity do you want the Jerries to partake in ? \n");
                                  printf("1 : Interact with fake Beth \n");
                                  printf("2 : Play golf \n");
                                  printf("3 : Adjust the picture settings on the TV \n");
                                  scanf("%s",tmp3);
                                  if (strlen(tmp3)!=1){
                                      memset(word, 0, sizeof tmp); //clean word
                                      memset(word, 0, sizeof tmp3); //clean word
                                      flag3=0;
                                  }

                                  if (strcmp(tmp3, "1") == 0) {
                                      flag3 = 1;
                                  } else if (strcmp(tmp3, "2") == 0) {
                                      flag3 = 2;
                                  } else if (strcmp(tmp3, "3") == 0)
                                      flag3 = 3;
                                  switch( flag3 ) {
                                      case 1:
                                          case8_1(JerryInOrder);
                                          memset(word, 0, sizeof tmp); //clean word
                                          memset(word, 0, sizeof tmp3); //clean word
                                          break;

                                      case 2:
                                          case8_2(JerryInOrder);
                                          memset(word, 0, sizeof tmp); //clean word
                                          memset(word, 0, sizeof tmp3); //clean word
                                          break;

                                      case 3:
                                          case8_3(JerryInOrder);
                                          memset(word, 0, sizeof tmp); //clean word
                                          memset(word, 0, sizeof tmp3); //clean word
                                          break;
                                      default:
                                      //    printf("Rick this option is not known to the daycare ! \n");
                                          memset(word, 0, sizeof tmp); //clean word
                                          memset(word, 0, sizeof tmp3); //clean word
                                          break;}
                      break;


                  case 9:

                            case9( JerryInOrder, JerryHash,  MsCp, planets);
                             break;
                          //close all
                          case 0:
                              memset(word, 0, sizeof tmp); //clean word
                              memset(word, 0, sizeof tmp);
                               break;

                         default: //if its not 1-9
                          printf("Rick this option is not known to the daycare ! \n");
                          memset(word, 0, sizeof tmp); //clean word
                          memset(word, 0, sizeof tmp);
                          break;}




              }
}


