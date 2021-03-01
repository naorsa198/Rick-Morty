#include "LinkedList.h"

typedef struct t_Node *Node;
typedef struct t_GenList *GenList;

struct t_Node
{
	Element selfData;
	Node nextNode;
	Node prevNode;
	GenList KeyList;
};



struct t_GenList
{
	int Length;
	Node head;
	Node end;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
//	DataInElementFunction Datafunc;
	EqualFunction isEqualKey;
	isEqualFunction isEqualValue;

};




void freeNode(GenList list,Node node)
{
    list->freeFunc(node->selfData);
	free(node);
}

GenList createLinkedList(copyFunction copyf, freeFunction freef, printFunction printfunc,EqualFunction isEqualKey)
{
	if(copyf==NULL || freef==NULL)
	{
		return NULL;
	}

	GenList List;
	List = (GenList)malloc(sizeof(struct t_GenList));
	if(List==NULL)
	{
		return NULL;
	}
	List->copyFunc=copyf;
	List->freeFunc=freef;
	List->printFunc=printfunc;
	//List->Datafunc=Datafunc;
	List->isEqualKey=isEqualKey;
	List->Length=0;
	List->head=NULL;
	List->end=NULL;
	return List;
}


void destroyList(GenList list)
{
    if(list->head!=NULL){
    Node tmp=NULL;
    Node tmp2=NULL;
    tmp=list->head;
    tmp2=tmp->nextNode;

    while(tmp->nextNode!=NULL)
    {
        freeNode(list,tmp);
        tmp=tmp2;
        tmp2=tmp->nextNode;
    }
    freeNode(list,tmp);}
    free(list);
}

status appendNode(GenList list, Element nodeData)
{
	if(list ==NULL || nodeData == NULL)
		return failure;

	Node tempNode=NULL;
	tempNode=(Node)malloc(sizeof(struct t_Node));
	if(tempNode==NULL)
		return failure;
	tempNode->selfData=list->copyFunc(nodeData);
//	tempNode->KeyList->Length++;   // each internal list of key its alawys start in 1 beachuse he is list of one node for himself
	if(list->Length!=0){
		list->end->nextNode=tempNode;
		tempNode->prevNode=list->end;
		list->end=tempNode;}
	else
		{(list->head=tempNode);
		list->head->prevNode=list->head;
			list->end=tempNode;
	list->end->prevNode=list->head;}

	//memory for node

	list->Length++;
	return success;
}

status deleteNode(GenList list, Element nodeData)
{
	if(list==NULL || nodeData==NULL)
	{
		return failure;
	}
	Node tempNode=list->head;
	if(list->isEqualKey(list->head->selfData,nodeData))//delete head
	{
		list->head=list->head->nextNode;
		//free tempNode..head
		freeNode(list,tempNode);
		list->Length--;
		return success;
	}

	if(list->isEqualKey(list->end->selfData,nodeData))//delete end
	{
        tempNode=list->end->prevNode;
		//free tempNode..end
		freeNode(list,list->end);
		list->end=tempNode;
        list->end->nextNode=NULL;
        list->Length--;
		return success;
	}

	int i=0;//delete between
	for(i=0;i<list->Length;i++)
	{
		if(list->isEqualKey(tempNode->selfData,nodeData))
			break;
	}

	tempNode->prevNode->nextNode=tempNode->nextNode;

	freeNode(list,tempNode);
	list->Length--;
	return success;
}

Element getDataByIndex(GenList list, int index)
{
	if(list==NULL)
	{
		return NULL;
	}

	if(index>=list->Length) //didnt find
		return NULL;
	Node tempNode=list->head;

	int i=0;
	for(i=0;i<index;i++)
	{
		tempNode=tempNode->nextNode;
	}

	return tempNode->selfData;
}

void displayList(GenList list)
{
    if(list->head!=NULL) {
        Node tmp=NULL;
        Node tmp2=NULL;
        tmp=list->head;
        tmp2=tmp->nextNode;

        while(tmp->nextNode!=NULL)
        {
            list->printFunc(tmp->selfData);
            tmp=tmp2;
            tmp2=tmp->nextNode;
        }

            list->printFunc(tmp->selfData);
        }
}

int getLengthList(GenList list)
{
	return list->Length;
}
//
//Element searchByKeyInList(GenList list, DataElement key)
//{
//	if(list==NULL || key==NULL)
//	{
//		return 0;
//	}
//	bool check;
//	Node tempNode=list->head;
//	Element value = NULL;
//	int i=0;
//	for(i=0;i<list->Length;i++)
//	{
//		//search for key here using keyFunc
//		check=list->Datafunc(tempNode->selfData,key);
//		if(check ==true)
//			return tempNode->selfData;
//
//		tempNode=tempNode->nextNode;
//	}
//	return NULL;
//}


Element searchByKeyInList(GenList list, DataElement val)
{
	if(list==NULL || val==NULL)
	{
		return NULL;
	}
	bool check =false;
	Node tempNode=list->head;
	int i=0;
	for(i=0;i<list->Length;i++)
	{
		//search for key here using keyFunc
		check=list->isEqualKey(tempNode->selfData,val);
		if(check ==true)
			return tempNode->selfData;

		tempNode=tempNode->nextNode;
	}
	return NULL;
}





GenList GetInternalList(GenList list,DataElement var)
{
	if(list==NULL || var==NULL)
		{
			return NULL;
		}
	bool check;
	Node tempNode=list->head;
	int i=0;
	for(i=0;i<list->Length;i++)
	{
		//search for key here using keyFunc
		check=list->isEqualKey(tempNode->selfData,var);
		if(check ==true)
			return tempNode->KeyList;
		}
	return NULL;

}


status destroyInternalList(GenList list)// destroy all the internal list in a list
{
	int i=0;
	if(list==NULL)
		return failure;
	GenList templist;
	Node temp =list->head;
	for(i=0; i<list->Length;i++){
		templist=temp->KeyList;
		if (templist==NULL){
			temp=list->head->nextNode;
			continue;}
	destroyList(templist);
	temp=temp->nextNode;
	templist=temp->KeyList;
	}
	destroyList(list);
	return success;
}


Element Copylist(Element kv)
{
	if(kv ==NULL)
		return NULL;

	GenList copyKv;
	copyKv= (GenList)malloc(sizeof(struct t_GenList));
	GenList copyKvold=NULL;
	copyKvold=(GenList)kv;


	copyKv->Length=copyKvold->Length;
	copyKv->copyFunc=copyKvold->copyFunc;
	copyKv->end=copyKvold->end;
	copyKv->freeFunc=copyKvold->freeFunc;
	copyKv->head=copyKvold->head;
	copyKv->isEqualKey=copyKvold->isEqualKey;
	copyKv->printFunc=copyKvold->printFunc;

	return copyKv;
}






status deleteNodeNoDeep(GenList list, Element nodeData)
{
    if(list==NULL || nodeData==NULL)
    {
        return failure;
    }
    Node tempNode=list->head;
    if(list->isEqualKey(list->head->selfData,nodeData))//delete head
    {
        list->head=list->head->nextNode;
        //free tempNode..head
        free(tempNode);
        list->Length--;
        return success;
    }
    Node endlst;
    if(list->isEqualKey(list->end->selfData,nodeData))//delete end
    {
        tempNode=list->end;
        endlst=list->end->prevNode;
        //free tempNode..end

        free(tempNode);
        list->end=endlst;
        list->end->nextNode=NULL;
        list->Length--;
        return success;
    }

    int i=0;//delete between
    while(tempNode->nextNode!=NULL)
    {
        if(list->isEqualKey(tempNode->selfData,nodeData)){
            tempNode->prevNode->nextNode=tempNode->nextNode;
            free(tempNode);
            list->Length--;
            return success;}
        tempNode=tempNode->nextNode;
    }


    return success;
}
