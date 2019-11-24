#ifndef GENODE_H
#define GENODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct GeNode
{
    void *Dt;
    struct GeNode *Next;
    struct GeNode *Previous;

}GeNode;

GeNode *new_GeNode(void *newData){

    GeNode *TmpNode = (GeNode *)malloc(sizeof(GeNode));

    TmpNode->Dt = newData;
    TmpNode->Next = 0;
    TmpNode->Previous = 0;

    return TmpNode;
}

GeNode *new_Empty_GeNode(){

    GeNode *TmpNode = (GeNode *)malloc(sizeof(GeNode));

    TmpNode->Dt = 0;
    TmpNode->Next = 0;
    TmpNode->Previous = 0;

    return TmpNode;
}

void freeGeNode(GeNode **Node){

    (*Node)->Previous = 0;
    (*Node)->Next = 0;
    free((*Node)->Dt);
    free(*Node);

}

#endif // GENODE_H