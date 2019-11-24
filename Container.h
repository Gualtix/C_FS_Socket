#ifndef CONTAINER_H
#define CONTAINER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fw/StringHandler.h"

#define Byte 1
#define Kilo 1024
#define Mega (Kilo * 1024)


typedef struct EBR{
    char  part_status;
    char  part_fit;
    int   part_start;
    int   part_size;
    int   part_next;
    char  part_name[16];

}EBR;

EBR* newEBR(){
    EBR* nEBR = (EBR*)malloc(sizeof(EBR));

    nEBR->part_status = '^';
    nEBR->part_fit    = '^';
    nEBR->part_start  = -1;
    nEBR->part_size   = -1;
    nEBR->part_next   = -1;
    memset(nEBR->part_name,'\0',16);
    strcpy(nEBR->part_name,"UNDEFINED");

    return nEBR;
}

typedef struct Partition
{
    char  part_status;
    char  part_type;
    char  part_fit[2];
    int   part_start;
    int   part_size;
    char  part_name[16];
    
}Partition;

Partition* newPartition(){
    Partition* nPart = (Partition*)malloc(sizeof(Partition));

    nPart->part_status   = '^';
    nPart->part_type     = '^';
    nPart->part_fit[0]   = '^';
    nPart->part_fit[1]   = '^';
    nPart->part_start    = -1;
    nPart->part_size     = -1;
    nPart->part_name[16] = '\0';
    memset(nPart->part_name,'\0',16);
    strcpy(nPart->part_name,"UNDEFINED_");
    
    return nPart;
}

typedef struct MBR
{
    int       mbr_tamano;
    char      mbr_fecha_creacion [17];
    int       mbr_disk_signature;
    char      disk_fit;
    Partition mbr_partition [4];
}MBR;

MBR* newMBR(){

    MBR* nMBR = (MBR*)malloc(sizeof(MBR));

    time_t Tmp = time(0);
    char ShapeDate[20];
    strftime(ShapeDate,128,"%d/%m/%y %H:%M:%S",localtime(&Tmp));

    nMBR->mbr_tamano = -1;
    memset(nMBR->mbr_fecha_creacion,'^',17);
    strcpy(nMBR->mbr_fecha_creacion,ShapeDate);
    nMBR->mbr_disk_signature = -1;
    nMBR->disk_fit = '^';
    nMBR->mbr_partition[0] = *newPartition();
    nMBR->mbr_partition[1] = *newPartition();
    nMBR->mbr_partition[2] = *newPartition();
    nMBR->mbr_partition[3] = *newPartition();

    nMBR->mbr_partition[0].part_name[10] = '1';
    nMBR->mbr_partition[1].part_name[10] = '2';
    nMBR->mbr_partition[2].part_name[10] = '3';
    nMBR->mbr_partition[3].part_name[10] = '4';

    return nMBR;

}


typedef struct InfoCatcher
{
    int   _size;
    char* _fit;
    char* _unit;
    char* _path;
    char* _type;
    char* _delete;
    char* _name;
    int   _add;
    char* _id;

    // ***** F2 *****
    char* _fs;
    char* _pwd;
    char* _usr;
    char* _grp;
    int   _ugo;
    int   _R;
    int   _P;
    char* _cont;
    char* _dest;
    char* _ruta;
    char* _file;
    char* txtData;
}InfoCatcher;

InfoCatcher* newInfoCatcher(){
    InfoCatcher* nwInfo = (InfoCatcher*)malloc(sizeof(InfoCatcher));
    nwInfo->_size   = -1;
    nwInfo->_fit    = NULL;
    nwInfo->_unit   = NULL;
    nwInfo->_path   = NULL;
    nwInfo->_type   = NULL;
    nwInfo->_delete = NULL;
    nwInfo->_name   = NULL;
    nwInfo->_add    = 1223556;
    nwInfo->_id     = NULL;

    // ***** F2 *****
    nwInfo->_fs     = NULL;
    nwInfo->_pwd    = NULL;
    nwInfo->_usr    = NULL;
    nwInfo->_grp    = NULL;
    nwInfo->_ugo    = -1;
    nwInfo->_R      = -1;
    nwInfo->_P      = -1;
    nwInfo->_cont   = NULL;
    nwInfo->_dest   = NULL;
    nwInfo->_ruta   = NULL;
    nwInfo->_file   = NULL;
    nwInfo->txtData = NULL;

    
    return nwInfo;
}

typedef struct Batch
{
    int   StartByte;
    int   Size;
    int   EndByte;
    char  Type;       
    char* PartName;
    int   Prev;
    int   Next;
    DoublyGenericList* LgParts;
}Batch;

Batch* newBatch(){
    Batch* Bt = (Batch*)malloc(sizeof(Batch));

    Bt->StartByte = -1;
    Bt->Size      = -1;
    Bt->EndByte   = -1;
    Bt->Type      = '^';
    Bt->PartName  = NULL;
    Bt->LgParts   = NULL;
    Bt->Prev      = - 1;
    Bt->Next      = - 1;

    
}





typedef struct Mounted_Part{
    char* ParName;
    int status;
    int index;
}Mounted_Part;

Mounted_Part* newMounted_Part(){    
    Mounted_Part* mntPart = (Mounted_Part*)malloc(sizeof(Mounted_Part));
    mntPart->ParName      = NULL;
    mntPart->status       = 0;
    mntPart->index        = -1;
}

typedef struct Disk_in_Use{
    char* CompletePathDir;
    Mounted_Part mntList [25];
    int status;
    int index;
}Disk_in_Use;


Disk_in_Use* newDisk_in_Use(){  
    Disk_in_Use* dsk_in = (Disk_in_Use*)malloc(sizeof(sizeof(Disk_in_Use)));
    dsk_in->CompletePathDir = NULL;
    int cnt = 0;
    while(cnt < 25){
        dsk_in->mntList[cnt] = *newMounted_Part();
        cnt++;
    }
    dsk_in->status = 0;
    dsk_in->index  = -1;
}


typedef struct Locat
{
    int Letter;
    int Num;
}Locat;



Locat* newLocat(){
    Locat* lcat = (Locat*)malloc(sizeof(Locat));
    lcat->Letter = -1;
    lcat->Num    = -1;
    return lcat;
}

typedef struct Mirror
{
    char* Original_DiskName;
    char* Mir_PathOnly;
    char* Mir_DiskName;   
    char* Mir_FullPath;
}Mirror;

Mirror* newMirror(char* FullPath){
    Mirror* Raid = (Mirror*)malloc(sizeof(Mirror));

    Raid->Original_DiskName = Path_Get_FileName(FullPath);
    Raid->Mir_PathOnly = Path_Get_Isolated(FullPath);

    Raid->Mir_DiskName = Concat_Izq_with_Der(newString("Mirror_"),Raid->Original_DiskName,'s','s');
    Raid->Mir_FullPath = Concat_Izq_with_Der(Raid->Mir_PathOnly,Raid->Mir_DiskName,'s','s');

    return Raid;
}









//int newLine_Flag;
//char* cmdString;


Disk_in_Use UsingDisk_List [25];










#endif // CONTAINER_H
