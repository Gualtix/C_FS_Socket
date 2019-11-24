#ifndef GLOVS_H
#define GLOVS_H

#include "Container.h"
#include "Container2.h"

typedef struct GLS{
    char*          CompletePathDir_of_Disk_inUse;
    SuperBlock*    SBinuse;
    Batch*         PartBatch_inUse;
    GroupUserInfo* LoggedUser;
    int Jr_Idex;
}GLS;

GLS*  Omni;
char* COMMS;
int   isRecovery;
int   JourColor;
DoublyGenericList* iList;



GLS* newGLS(){
    
    GLS* Omni = (GLS*)malloc(sizeof(GLS));

    Omni->CompletePathDir_of_Disk_inUse = NULL;
    Omni->SBinuse = NULL;
    Omni->PartBatch_inUse = NULL;
    Omni->LoggedUser = NULL;
    Omni->Jr_Idex = -1;

    return Omni;
}

#endif // GLOVS_H




