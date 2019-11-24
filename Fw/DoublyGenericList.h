#ifndef DOUBLYGENERICLIST_H
#define DOUBLYGENERICLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "GeNode.h"

typedef struct DoublyGenericList
{
    int Length;
    GeNode *First;
    GeNode *Last;

    //Last Inserted

    //Last Removed

} DoublyGenericList;

//(^< ............ ............ ............
DoublyGenericList *new_DoublyGenericList(){

    DoublyGenericList *TmpGeList = (DoublyGenericList *)malloc(sizeof(DoublyGenericList));

    TmpGeList->Length = 0;
    TmpGeList->First = 0;
    TmpGeList->Last = 0;
    TmpGeList->Length = 0;

    return TmpGeList;
}


//(^< ............ ............ ............ i s   E m p t y
int isEmpty(int Length){
    return (Length == 0);
}

//(^< ............ ............ ............ i s   V a l i d I n d e x
int isValidIndex(int Length,int index){
    return (index >= 0 && index < Length);
}

//(^< ............ ............ ............ E M P T Y   I N S E R T
int EmptyInsert(DoublyGenericList * TmpGeList,void *newData){
    if(isEmpty(TmpGeList->Length)){

        GeNode *TmpNode = new_GeNode(newData);

        TmpGeList->First = TmpNode;
        TmpGeList->Last = TmpNode;

        TmpGeList->Length++;

        return 1;
    }
    else{
        return 0;
    }
}

//(^< ............ ............ ............ F R O N T   I N S E R T
void FrontInsert(DoublyGenericList *TmpGeList,void *newData){

    if(EmptyInsert(TmpGeList,newData)){
        return;
    }
    else{

        GeNode *TmpNode = new_GeNode(newData);

        TmpNode->Next = TmpGeList->First;
        TmpGeList->First->Previous = TmpNode;
        TmpGeList->First = TmpNode;

        TmpGeList->Length++;
    }
}

//(^< ............ ............ ............ E N D   I N S E R T
void EndInsert(DoublyGenericList *TmpGeList,void *newData){

    if(EmptyInsert(TmpGeList,newData)){
        return;
    }
    else{

        GeNode *TmpNode = new_GeNode(newData);

        TmpNode->Previous = TmpGeList->Last;
        TmpGeList->Last->Next = TmpNode;
        TmpGeList->Last = TmpNode;

        TmpGeList->Length++;
    }
}

//(^< ............ ............ ............ g e t   N O D E   b y   I N D E X
GeNode *getNodebyIndext_Recusively(GeNode *TmpNode ,int index){

    if(index == 0){
        return TmpNode;
    }
    else{
        TmpNode = TmpNode->Next;
        index--;
        return getNodebyIndext_Recusively(TmpNode,index);
    }
}

//(^< ............ ............ ............ g e t   N O D E   b y   I N D E X
GeNode *getNodebyIndex(DoublyGenericList *TmpGeList,int index){
    if(isValidIndex(TmpGeList->Length,index)){
        return getNodebyIndext_Recusively(TmpGeList->First,index);
    }
    else{
        return 0;
    }
}

//(^< ............ ............ ............ S P E C I F I C   I N S E R T
int SpecificInsert(DoublyGenericList *TmpGeList,void *newData,int index){
    if(isValidIndex(TmpGeList->Length,index)){
        //(^< ............ FrontInsert
        if(TmpGeList->Length == 0){
            FrontInsert(TmpGeList,newData);
            return 1;
        }
        //(^< ............ IntermediateInsert
        else{
            
            GeNode *OldNode = getNodebyIndex(TmpGeList,index);
            GeNode *NewNode = new_GeNode(newData);
            
            OldNode->Previous->Next = NewNode;
            NewNode->Previous = OldNode->Previous;
            
            OldNode->Previous = NewNode;
            NewNode->Next = OldNode;
            
            TmpGeList->Length++;
            
            return 1;
        }
    }
    else{
        //(^< ............ EndInsert
        if(TmpGeList->Length == index){
            EndInsert(TmpGeList,newData);
            return 1;
        }
        else{
            return 0;
        }
    }
}

//(^< ............ ............ ............ F R O N T   R E M O V E
GeNode* DQNode(DoublyGenericList *TmpGeList){
    
    if(TmpGeList->Length == 1){
        GeNode *TmpNode = TmpGeList->First;
        
        TmpGeList->First = 0;
        TmpGeList->Last = 0;
        
        TmpGeList->Length--;
        
        return TmpNode;
    }
    
    if(!isEmpty(TmpGeList->Length)){
        
        GeNode *TmpNode = TmpGeList->First;
     
        TmpGeList->First = TmpGeList->First->Next;
        TmpGeList->First->Previous = 0;
        
        TmpNode->Next = 0;
        TmpNode->Previous = 0;
        
        TmpGeList->Length--;
        
        //void *TmpData = TmpNode->Dt;
        
        //freeGeNode(&TmpNode);
        
        return TmpNode;
    }
    else{
        return NULL;
    }
}

//(^< ............ ............ ............ F R O N T   R E M O V E
void *FrontRemove(DoublyGenericList *TmpGeList){
    
    if(TmpGeList->Length == 1){
        GeNode *TmpNode = TmpGeList->First;
        
        TmpGeList->First = 0;
        TmpGeList->Last = 0;
        
        TmpGeList->Length--;
        
        return TmpNode->Dt;
    }
    
    if(!isEmpty(TmpGeList->Length)){
        
        GeNode *TmpNode = TmpGeList->First;
     
        TmpGeList->First = TmpGeList->First->Next;
        TmpGeList->First->Previous = 0;
        
        TmpNode->Next = 0;
        TmpNode->Previous = 0;
        
        TmpGeList->Length--;
        
        void *TmpData = TmpNode->Dt;
        
        //freeGeNode(&TmpNode);
        
        return TmpData;
    }
    else{
        return 0;
    }
}

//(^< ............ ............ ............ E N D   R E M O V E
void *EndRemove(DoublyGenericList *TmpGeList){
    
    if(TmpGeList->Length == 1){
        GeNode *TmpNode = TmpGeList->Last;
        
        TmpGeList->First = 0;
        TmpGeList->Last = 0;
        
        TmpGeList->Length--;
        
        return TmpNode->Dt;
    }
    
    if(!isEmpty(TmpGeList->Length)){
        
        GeNode *TmpNode = TmpGeList->Last;
        
        TmpGeList->Last = TmpGeList->Last->Previous;
        TmpGeList->Last->Next = 0;
        
        TmpNode->Next = 0;
        TmpNode->Previous = 0;
        
        
        TmpGeList->Length--;
        
        void *TmpData = TmpNode->Dt;
        
        //freeGeNode(&TmpNode);
       
        return TmpData;
    }
    else{
        return 0;
    }
}

//(^< ............ ............ ............ S P E C I F I C   R E M O V E
int SpecificRemove(DoublyGenericList *TmpGeList,int index){
    if(isValidIndex(TmpGeList->Length,index) && index != (TmpGeList->Length - 1)){
        
        //(^< ............ FrontRemove
        if(TmpGeList->Length == 1 || index == 0){
            FrontRemove(TmpGeList);
            return 1;
        }
        //(^< ............ IntermediateRemove
        else{
            
            GeNode *OldNode = getNodebyIndex(TmpGeList,index);
            
            OldNode->Previous->Next = OldNode->Next;
            OldNode->Next->Previous = OldNode->Previous;
            
            OldNode->Previous = 0;
            OldNode->Next = 0;
            
            freeGeNode(&OldNode);
            TmpGeList->Length--;
            
            return 1;
        }
    }
    else{
        //(^< ............ EndRemove
        if(TmpGeList->Length == index || index == (TmpGeList->Length - 1)){
            EndRemove(TmpGeList);
            return 1;
        }
        else{
            return 0;
        }
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ S T A C K
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void Push(DoublyGenericList *TmpGeList,void *newData){
    FrontInsert(TmpGeList,newData);
}

GeNode *Pop(DoublyGenericList *TmpGeList){
    return (GeNode*)EndRemove(TmpGeList);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Q U E U E
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void EnQueue(DoublyGenericList *TmpGeList,void *newData){
    EndInsert(TmpGeList,newData);
}

GeNode *DeQueue(DoublyGenericList *TmpGeList){
    return (GeNode*)FrontRemove(TmpGeList);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ P R I N T
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void PrintGeneric(DoublyGenericList *TmpGeList, void (*GenFunc)(void *GenericData))
{
    if(!isEmpty(TmpGeList->Length)){
        
        GeNode *Current = TmpGeList->First;
    
        while(Current != 0){
            GenFunc(Current->Dt);
            Current = Current->Next;
        }
    }
}

#endif // DOUBLYGENERICLIST_H
