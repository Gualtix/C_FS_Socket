#ifndef F1_DO_H
#define F1_DO_H

#include "Container.h"
#include "Fw/Helper.h"
#include "Belong.h"
#include "Rep/F1_Rep.h"
#include "Rep/F2_Rep.h"

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ M K D I S K
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void SetDiskSize(char* CompletePathDir,int DiskSize,char Unit){

    FILE* Fl = fopen(CompletePathDir,"wb+");
    char Bf[1024];

    if(Fl){

        memset(Bf,'\0',1024);

        int cnt = DiskSize;

        if('k' == Unit){
            while (cnt > 0) {
                fwrite(Bf,1024,1,Fl);
                cnt--;
            }
        }
        else{
            cnt = DiskSize * 1024;
            while (cnt > 0) {
                fwrite(Bf,1024,1,Fl);
                cnt--;
            }
        }
        fclose(Fl);
    }
}

void SetMBR_to_Disk(char* CompletePathDir,int DiskSize,char Unit,char Fit){

    FILE* Fl = fopen(CompletePathDir,"r+");

    if(Fl){
        int RandomID = rand()%(100);
        MBR* MBR_DEF = newMBR();

        MBR_DEF->mbr_tamano = CalcSize_in_Bytes(DiskSize,Unit);
        MBR_DEF->mbr_disk_signature = RandomID;
        MBR_DEF->disk_fit = Fit;

        fseek(Fl,0,SEEK_SET);
        fwrite(MBR_DEF,sizeof(MBR),1,Fl);
        fclose(Fl);
    }
}

void mkdisk_do(InfoCatcher* nwInf){

    char* PathOnly = Path_Get_Isolated(nwInf->_path);
    CreatePathDir(PathOnly);
    SetDiskSize(nwInf->_path,nwInf->_size,nwInf->_unit[0]);
    SetMBR_to_Disk(nwInf->_path,nwInf->_size,nwInf->_unit[0],nwInf->_fit[0]);

    char* DiskName = Path_Get_FileName(nwInf->_path);

    //Mirror
    Mirror* Raid = newMirror(nwInf->_path);
    SetDiskSize(Raid->Mir_FullPath,nwInf->_size,nwInf->_unit[0]);
    SetMBR_to_Disk(Raid->Mir_FullPath,nwInf->_size,nwInf->_unit[0],nwInf->_fit[0]);

    printf("\n");
    printf("MKDISK SUCCESS:   -> %s   <-   Creado Correctamente\n",DiskName);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ R M D I S K
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void rmdisk_do(InfoCatcher* nwInf){
    char* DiskName = Path_Get_FileName(nwInf->_path);
    FILE* Fl = fopen(nwInf->_path,"r");
    if(Fl){
        fclose(Fl);
        printf("\n");
        printf("RMDISK WARNING: Esta Seguro de Eliminar   -> %s <-   ?\n",DiskName);
        printf("Y = Yes , Any Other Key = No \n");

        char Op;
        Op = getchar();
        if(Op == '\n' || Op == '\r'){
            Op = getchar();
        }

        if(putchar(tolower(Op)) == 'y' ){
            remove(nwInf->_path);
            //Mirror
            Mirror* Raid = newMirror(nwInf->_path);
            remove(Raid->Mir_FullPath);
            
            printf("\n");
            printf("RMDISK SUCCESS:   -> %s <-   Eliminado con Exito\n",DiskName);
            getchar();
        }
        else{
            printf("\n");
            printf("RMDISK WARNING: Operacion Eliminar Disco Cancelada\n");
            getchar();
        }
    }
    else{
        printf("\n");
        printf("RMDISK ERROR: Disco   -> %s <-   , NO Encontrado\n",DiskName);
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ F D I S K
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............



void Delete_Part(InfoCatcher* nwInf, MBR* Disk){

    
    Batch* Prt = getBatch_By_PartName(nwInf->_path,Disk,nwInf->_name);
    if(Prt == NULL){
        printf("\n");
        printf("FDISK ERROR: La Particion   -> %s <-   No Existe\n",nwInf->_name);
        getchar();
        return;
    }

    int Op = DeleteAsk(nwInf->_name);
    if(Op == 0){
        return;
    }

    if(strcasecmp(nwInf->_delete,"fast") == 0 || strcasecmp(nwInf->_delete,"full") == 0){

        if(Prt->Type == 'p' || Prt->Type == 'e'){
            int index = MBRPartArray_GetIndex_By_PartName(Disk,Prt->PartName);
            Disk->mbr_partition[index] = *(newPartition());

            Ascending_MBRPartArray_BubbleSort(Disk);
            UpdateMBR(nwInf->_path,Disk);
        }

        if(Prt->Type == 'q'){

            if(Prt->Prev > -1){
                EBR* Prev = LoadEBR(nwInf->_path,Prt->Prev);
                Prev->part_next = Prt->Next;
                UpdateEBR(Prev,nwInf->_path);
            }
            else{
                EBR* DefaultEBR = LoadEBR(nwInf->_path,Prt->StartByte);
                DefaultEBR->part_fit = '^';
                DefaultEBR->part_size = sizeof(EBR);
                DefaultEBR->part_status = '^';
                memset(DefaultEBR->part_name,'\0',16);
                strcpy(DefaultEBR->part_name,"UNDEFINED");
                UpdateEBR(DefaultEBR,nwInf->_path);
            }
        }

        if(strcasecmp(nwInf->_delete,"fast") == 0){
            printf("\n");
            printf("FDISK SUCESS: Particion   -> %s <-   Eliminada Exitosamente por Fast Delete\n",nwInf->_name);
            getchar();
            return;
        }

    }
    if(strcasecmp(nwInf->_delete,"full") == 0){
        printf("\n");
        printf("FDISK SUCESS: Particion   -> %s <-   Eliminada Exitosamente por Full Delete\n",nwInf->_name);
        getchar();
        return;
    }

    printf("\n");
    printf("FDISK ERROR: Parametro -delete:   -> %s <-   No Valido\n",nwInf->_name);
    printf("FDISK WARNING: Operacion Eliminar Particion Cancelada\n" );
    getchar();
    return;
}

void fdisk_do(InfoCatcher* nwInf, MBR* Disk){

    //(^< ............ ............ ............ Space Validation
    DoublyGenericList* batchList = getBatchList_FromDisk(nwInf->_path,Disk);

    char* FType =  newString("Primer Ajuste");

    if(Disk->disk_fit == 'f'){
        Isolate_SpaceBatch(batchList);
    }

    if(Disk->disk_fit == 'b'){
        get_Ascending_BatchSpace_List(batchList);
        FType = newString("Mejor Ajuste");
    }

    if(Disk->disk_fit == 'w'){
        get_Descending_BatchSpace_List(batchList);
        FType = newString("Peor Ajuste");
    }

    //(^< ............ ............ ............ Regular
    if(nwInf->_type[0] != 'l'){

        Batch* tmp = get_First_SpaceBatch_That_Fits(batchList,nwInf->_size);
        if(tmp == NULL){
            printf("\n");
            printf("FDISK ERROR: No Existe Espacio para Crear La Particion\n");
            return;
        }

        int index = MBRPartArray_GetAvailableIndex(Disk);

        Partition* Part = newPartition();

        strcpy(Part->part_name,nwInf->_name);
        strcpy(Part->part_fit,nwInf->_fit);
        Part->part_type = nwInf->_type[0];
        Part->part_size = nwInf->_size;
        Part->part_start = tmp->StartByte;
        Part->part_status = '0';

        Disk->mbr_partition[index] = *Part;

        if(Part->part_type == 'e'){
            EBR* eB = newEBR();
            eB->part_start = Part->part_start;
            UpdateEBR(eB,nwInf->_path);
        }

        Ascending_MBRPartArray_BubbleSort(Disk);
        UpdateMBR(nwInf->_path,Disk);

        printf("\n");
        printf("FDISK SUCESS: Particion   -> %s <-   Creada Exitosamente por %s\n",nwInf->_name,FType);
        return;
        
    }
    //(^< ............ ............ ............ Logic
    else{

        Batch* ext = getExtended_Batch(batchList);
        Batch* tmp = get_First_SpaceBatch_That_Fits(ext->LgParts,nwInf->_size);

        //(^< ............ ............ ............ ............ ............
        batchList = getBatchList_FromDisk(nwInf->_path,Disk);

        int ext_index = MBRPartArray_GetIndex_By_PartName(Disk,ext->PartName);
        Partition extPart = Disk->mbr_partition[ext_index];

        FType =  newString("Primer Ajuste");

        if(extPart.part_fit[0] == 'f'){
            Isolate_SpaceBatch(batchList);
        }

        if(extPart.part_fit[0] == 'b'){
            get_Ascending_BatchSpace_List(batchList);
            FType = newString("Mejor Ajuste");
        }

        if(extPart.part_fit[0] == 'w'){
            get_Descending_BatchSpace_List(batchList);
            FType = newString("Peor Ajuste");
        }
        //(^< ............ ............ ............ ............ ............

        if(tmp == NULL){
            printf("\n");
            printf("FDISK ERROR: No Existe Espacio para Crear La Particion\n");
            return;
        }

        EBR* DefaultEBR = LoadEBR(nwInf->_path,ext->StartByte);
        
        EBR* new_lgPart = newEBR();
        
        //if(DefaultEBR->part_start == tmp->Prev && strcasecmp(DefaultEBR->part_name,"UNDEFINED") == 0){
        if(strcasecmp(DefaultEBR->part_name,"UNDEFINED") == 0 && DefaultEBR->part_next > -1){

            new_lgPart->part_start = ext->StartByte;
            new_lgPart->part_size  = nwInf->_size;
            new_lgPart->part_next  = tmp->Next;
            new_lgPart->part_status = '0';
            strcpy(new_lgPart->part_name,nwInf->_name);
            new_lgPart->part_fit = nwInf->_fit[0];
            UpdateEBR(new_lgPart,nwInf->_path);

            GenerateDiskRender("/home/archivos/fase1/Disco1.disk","/home/wrm/Desktop/","Ds.dot");

            printf("\n");
            printf("FDISK SUCESS: Particion Logica   -> %s <-   Creada Exitosamente por %s\n",nwInf->_name,FType);
            return;
        }
    

        if(DefaultEBR->part_size == -1){

                new_lgPart->part_start = DefaultEBR->part_start;
                new_lgPart->part_size = nwInf->_size;
                new_lgPart->part_next = -1;
                new_lgPart->part_status = '0';
                strcpy(new_lgPart->part_name,nwInf->_name);
                new_lgPart->part_fit = nwInf->_fit[0];
                UpdateEBR(new_lgPart,nwInf->_path);

            }
            else{

                EBR* prev_lgPart = LoadEBR(nwInf->_path,tmp->Prev);

                new_lgPart->part_start = tmp->StartByte;
                new_lgPart->part_size  = nwInf->_size;
                new_lgPart->part_next  = tmp->Next;
                new_lgPart->part_status = '0';
                strcpy(new_lgPart->part_name,nwInf->_name);
                new_lgPart->part_fit = nwInf->_fit[0];

                prev_lgPart->part_next = new_lgPart->part_start;
                new_lgPart->part_next  = tmp->Next;

                UpdateEBR(prev_lgPart,nwInf->_path);
                UpdateEBR(new_lgPart,nwInf->_path);
                
            }
    
            printf("\n");
            printf("FDISK SUCESS: Particion Logica   -> %s <-   Creada Exitosamente por %s\n",nwInf->_name,FType);
            return;
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ F 2
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void mkfs_do(InfoCatcher* nwInf){

    setOmni(nwInf->_id);

    if(strcasecmp(nwInf->_type,"fast") == 0){
        Fast_PartFormat();
    }

    if(strcasecmp(nwInf->_type,"full") == 0){
        Full_PartFormat();
    }

    Format_to_EXT3();
    Load_Defaut_txt(nwInf);
    
    Omni = newGLS();
}

void mkgrp_do(InfoCatcher* nwInf){

    DoublyGenericList*  grpList = getGroupsList();
    DoublyGenericList*  usrList = getUsersList();
    GroupUserInfo* gu = newGrus();

    if(grpList != NULL){
        gu->ID = grpList->Length + 1;
        gu->Type = 'g';
        gu->GrpName = nwInf->_name;
    }
    EnQueue(grpList,gu);
    txtUsers_Update(grpList,usrList);
}

void rmgrp_do(InfoCatcher* nwInf){

    DoublyGenericList*  grpList = getGroupsList();
    DoublyGenericList*  usrList = getUsersList();

    int Lm = grpList->Length;
    int cnt = 0;
    int found = 0;
    while(cnt < Lm){
        GroupUserInfo* tmp = (GroupUserInfo*)getNodebyIndex(grpList,cnt)->Dt;
        if(strcasecmp(nwInf->_name,tmp->GrpName) == 0){
            tmp->ID = 0;
            found++;
            break;
        }
        cnt++;
    }

    txtUsers_Update(grpList,usrList);

    //grpList = getGroupsList();
    //usrList = getUsersList();

    //int ask = 554;
}

void mkusr_do(InfoCatcher* nwInf){

    DoublyGenericList*  grpList = getGroupsList();
    DoublyGenericList*  usrList = getUsersList();
    GroupUserInfo* gu = newGrus();

    int grpEx = grpExists(nwInf->_grp,grpList);
    int usrEx = usrExists(nwInf->_usr,usrList);

    if(usrList != NULL){
        gu->ID = usrList->Length + 1;
        gu->Type = 'u';
        gu->GrpName = nwInf->_grp;
        gu->UsrName = nwInf->_usr;
        gu->Password = nwInf->_pwd;
    }

    EnQueue(usrList,gu);
    txtUsers_Update(grpList,usrList);
}

void rmusr_do(InfoCatcher* nwInf){

    DoublyGenericList*  grpList = getGroupsList();
    DoublyGenericList*  usrList = getUsersList();

    int Lm = usrList->Length;
    int cnt = 0;
    int found = 0;
    while(cnt < Lm){
        GroupUserInfo* tmp = (GroupUserInfo*)getNodebyIndex(usrList,cnt)->Dt;
        if(strcasecmp(nwInf->_usr,tmp->UsrName) == 0){
            tmp->ID = 0;
            found++;
            break;
        }
        cnt++;
    }
    txtUsers_Update(grpList,usrList);
}

void login_do(InfoCatcher* nwInf){
    DoublyGenericList* usrList = getUsersList();
    GroupUserInfo* gu  = getUSR_by_Name(nwInf->_usr,usrList);

    DoublyGenericList* grpList = getGroupsList();
    GroupUserInfo* tmp = getGRP_by_Name(gu->GrpName,grpList);

    gu->GrpID = tmp->ID;

    Omni->LoggedUser = gu;
}

void cat_do(InfoCatcher* nwInf){
    //nwInf->_path = newString(nwInf->_file);
    Existence* ex = vFF_Exists(nwInf->_file);
    char* txt = ReadFile(nwInf->_file);
    printf("\n");
    printf("Contenido del Archivo %s: %s\n",ex->FFName,txt);

}

void loss_do(InfoCatcher* nwInf){

    Mounted_Part* mP = getPartMounted_By_vID(nwInf->_id);
    char* Bf = newString(1024);
    //memset(Bf,'x',1024);
    setOmni(nwInf->_id);

    int iN = Omni->SBinuse->s_inodes_count;

    int Part_StartByte = Omni->PartBatch_inUse->StartByte;
    int Part_EndByte   = Omni->PartBatch_inUse->EndByte;

    int Jr_EndByte = Part_StartByte + (sizeof(SuperBlock) * iN) + sizeof(Journaling);

    int LossSize = Part_EndByte - Jr_EndByte;

    int Div = LossSize / 1024;
    int Res = LossSize % 1024;

    FILE* Fl = fopen(Omni->CompletePathDir_of_Disk_inUse,"rb+");
    if(Fl){
        int i = 0;
        int Last = 0;
        while(i < Div){
            fseek(Fl,Jr_EndByte + (i * 1024),SEEK_SET);
            fwrite(Bf,1024,1,Fl);
            Last = Jr_EndByte + (i * 1024);
            i++;
        }
        if(Res > 0){
            Last = Last + 1024;
            Bf = newString(Res);
            fseek(Fl,Last,SEEK_SET);
            fwrite(Bf,1024,1,Fl);
            Last = Last + Res;
            int ee = 0;
        }

        fclose(Fl);
    }
    Omni = newGLS();
}

void ren_do(InfoCatcher* nwInf){
    Existence* ex = vFF_Exists(nwInf->_path);
    SeekInfo* sk = CompleteSeeker(ex->iNodeFather,ex->FFName);
    FolderBlock* Fb = (FolderBlock*)BinLoad_Str(sk->FB_Bit_ID,"FolderBlock");

    strcpy(Fb->b_content[sk->FB_Index].b_name,newString(nwInf->_name));
    BinWrite_Struct(Fb,sk->FB_Bit_ID,"FolderBlock");
}

int mkfile_do(InfoCatcher* nwInf){

    FileFolderInfo* ffInf = get_FFInfo(nwInf);
    int Deepest_Bit_ID = make_newFolder(nwInf);
    if(Deepest_Bit_ID > -1){
        GroupUserInfo* ggs = getGRP_by_Name(Omni->LoggedUser->GrpName,getGroupsList());
        int nwFL_Bit_ID = allocate_newFile(Deepest_Bit_ID,ffInf->FileName,ffInf->txtData,664,Omni->LoggedUser->ID,ggs->ID);
        return nwFL_Bit_ID;
    }
    else{
        return -1;
    }
}

int mkdir_do(InfoCatcher* nwInf){
    int Deepest_Bit_ID = make_newFolder(nwInf);
    return Deepest_Bit_ID;
}

void edit_do(InfoCatcher* nwInf){

    TheLast* tl = getTheLast(nwInf->_path);
    Existence* ex = vFF_Exists(nwInf->_path);

    char* OldTxt = ReadFile(nwInf->_path);
    char* NewTxt = Concat_Izq_with_Der(OldTxt,newString(nwInf->_cont),'s','s');
    EditFile(nwInf->_path,NewTxt);
}

void mv_do(InfoCatcher* nwInf){

    TheLast* tlSource = getTheLast(nwInf->_path);
    Existence* exSource = vFF_Exists(nwInf->_path);

    TheLast* tlDest = getTheLast(nwInf->_dest);
    Existence* exDest = vFF_Exists(nwInf->_dest);


    //-------------------------------------->Fuente

    SeekInfo* Origin = CompleteSeeker(exSource->iNodeFather,tlSource->Name);
    SeekInfo* Dest   = CompleteSeeker(exDest->iNodeFather,tlDest->Name);

    FolderBlock* FolderB = (FolderBlock*)BinLoad_Str(Origin->FB_Bit_ID,"FolderBlock");
    memset(FolderB->b_content[Origin->FB_Index].b_name,'\0',12);
    FolderB->b_content[Origin->FB_Index].b_inodo = -1;

    BinWrite_Struct(FolderB,Origin->FB_Bit_ID,"FolderBlock");

    //-------------------------------------->Destino
    pushMoved(Dest->iNode_Bit_ID,Origin->iNode_Bit_ID,tlSource->Name);
    
    //-------------------------------------->Actualizacion de Padre
    if(tlSource->istxt == 0){
        setNewFather(Origin->iNode_Bit_ID,Dest->iNode_Bit_ID);
    }
    //FatherUpdate(Dest->iNode_Bit_ID);

}

void find_do(InfoCatcher* nwInf){
    //CompleteSeeker
    //TheLast* tl = getTheLast(nwInf->_path);
    Existence* ex = vFF_Exists(nwInf->_path);
    //SeekInfo* nwSI = CompleteSeeker(ex->iNode,nwInf->_name);
    //SeekInfo* nwSI = SuperSeeker(ex->iNode,nwInf->_name);

    //SeekInfo* Ori = CompleteSeeker(0,"fase1");
    //SeekInfo* Niu = SuperSeeker(0,"fase1");

    /*
    while(nwSI->Travel->Length > 0){
        char* tmp = (char*)DeQueue(nwSI->Travel);
        printf("%s\n",tmp);
    }
    */
}

void chgrp_do(InfoCatcher* nwInf){

    char* OldPassword= newString(Omni->LoggedUser->Password);
    char* NewGRPName = newString(nwInf->_grp);
    char* OldUser = newString(nwInf->_usr);
    

    DoublyGenericList*  grpList = getGroupsList();
    DoublyGenericList*  usrList = getUsersList();

    int Lm = grpList->Length;
    int cnt = 0;
    int found = 0;
    while(cnt < Lm){
        GroupUserInfo* tmp = (GroupUserInfo*)getNodebyIndex(usrList,cnt)->Dt;
        if(strcasecmp(OldUser,tmp->UsrName) == 0){
            tmp->GrpName = NewGRPName;
            found++;
            break;
        }
        cnt++;
    }

    txtUsers_Update(grpList,usrList);

  

    //rmusr_do(nwInf);
    //nwInf->_pwd = OldPassword;
    //mkusr_do(nwInf);

}

void chmod_do(InfoCatcher* nwInf){

    TheLast* tl = getTheLast(nwInf->_path);
    Existence* ex = vFF_Exists(nwInf->_path);

    Inode* iN  = (Inode*)BinLoad_Str(ex->iNode,"Inode");

    if(nwInf->_R != 1){
        
        printf("\n");
        printf("%s INFO: Permisos de %s:   -> %i <-   Cambiados a:   -> %i <-   \n","CHMOD",tl->Name,iN->i_perm,nwInf->_ugo);
        iN->i_perm = nwInf->_ugo;
        BinWrite_Struct(iN,ex->iNode,"Inode");

    }

    if(nwInf->_R == 1 && tl->istxt == 1){
        printf("\n");
        printf("%s INFO: Permisos de %s:   -> %i <-   Cambiados a:   -> %i <-   \n","CHMOD",tl->Name,iN->i_perm,nwInf->_ugo);
        iN->i_perm = nwInf->_ugo;
        BinWrite_Struct(iN,ex->iNode,"Inode");

    }

    if(nwInf->_R == 1){
        SeekInfo* nwSi = SuperSeeker(ex->iNode,"distronone");

        //Father Change
        printf("\n");
        printf("%s INFO: Permisos de %s:   -> %i <-   Cambiados a:   -> %i <-   \n","CHMOD",tl->Name,iN->i_perm,nwInf->_ugo);
        iN->i_perm = nwInf->_ugo;
        BinWrite_Struct(iN,ex->iNode,"Inode");

        while(iList->Length > 0){
            
            SeekInfo* tmp = (SeekInfo*)DeQueue(iList);

            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(tmp->FB_Bit_ID,"FolderBlock");            
            Inode* inn = (Inode*)BinLoad_Str(Fb->b_content[tmp->FB_Index].b_inodo,"Inode");

            if(inn->i_uid != Omni->LoggedUser->ID && strcasecmp(Omni->LoggedUser->UsrName,"root") != 0){
                printf("\n");
                printf("%s ERROR: El Usuario Logeado No es Propietario de:   -> %s <-\n","CHMOD",Fb->b_content[tmp->FB_Index].b_name);
                continue;
            }

            printf("\n");
            printf("%s INFO: Permisos de %s:   -> %i <-   Cambiados a:   -> %i <-   \n","CHMOD",Fb->b_content[tmp->FB_Index].b_name,inn->i_perm,nwInf->_ugo);

            inn->i_perm = nwInf->_ugo;
            BinWrite_Struct(inn,Fb->b_content[tmp->FB_Index].b_inodo,"Inode");
        }
    }
}

void chown_do(InfoCatcher* nwInf){
    TheLast* tl = getTheLast(nwInf->_path);
    Existence* ex = vFF_Exists(nwInf->_path);

    Inode* iN  = (Inode*)BinLoad_Str(ex->iNode,"Inode");

    DoublyGenericList* usrList = getUsersList();
    GroupUserInfo* us = getUSR_by_Name(nwInf->_usr,usrList);

    char* OldOwner = getUSR_by_ID(iN->i_uid)->UsrName;

    if(nwInf->_R != 1){
        
        printf("\n");
        printf("%s INFO: Propietario de %s:   -> %s <-   Ahora es Propiedad de:   -> %s <-   \n","CHOWN",tl->Name,OldOwner,us->UsrName);
        iN->i_uid = us->ID;
        BinWrite_Struct(iN,ex->iNode,"Inode");

    }

    if(nwInf->_R == 1 && tl->istxt == 1){
        printf("\n");
        printf("%s INFO: Propietario de %s:   -> %s <-   Ahora es Propiedad de:   -> %s <-   \n","CHOWN",tl->Name,OldOwner,us->UsrName);
        iN->i_uid = us->ID;
        BinWrite_Struct(iN,ex->iNode,"Inode");

    }

    if(nwInf->_R == 1){
        SeekInfo* nwSi = SuperSeeker(ex->iNode,"distronone");

        //Father Change
        printf("\n");
        printf("%s INFO: Propietario de %s:   -> %s <-   Ahora es Propiedad de:   -> %s <-   \n","CHOWN",tl->Name,OldOwner,us->UsrName);
        iN->i_uid = us->ID;
        BinWrite_Struct(iN,ex->iNode,"Inode");

        while(iList->Length > 0){
            
            SeekInfo* tmp = (SeekInfo*)DeQueue(iList);

            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(tmp->FB_Bit_ID,"FolderBlock");            
            Inode* inn = (Inode*)BinLoad_Str(Fb->b_content[tmp->FB_Index].b_inodo,"Inode");

            OldOwner = getUSR_by_ID(inn->i_uid)->UsrName;

            if(inn->i_uid != Omni->LoggedUser->ID && strcasecmp(Omni->LoggedUser->UsrName,"root") != 0){
                printf("\n");
                printf("%s ERROR: El Usuario Logeado No es Propietario de:   -> %s <-\n","CHOWN",Fb->b_content[tmp->FB_Index].b_name);
                continue;
            }

            printf("\n");
            printf("%s INFO: Propietario de %s:   -> %s <-   Ahora es Propiedad de:   -> %s <-   \n","CHOWN",Fb->b_content[tmp->FB_Index].b_name,OldOwner,us->UsrName);

            inn->i_uid = us->ID;
            BinWrite_Struct(inn,Fb->b_content[tmp->FB_Index].b_inodo,"Inode");
        }
    }
}

void rem_do(InfoCatcher* nwInf){

    TheLast* tl = getTheLast(nwInf->_path);
    Existence* ex = vFF_Exists(nwInf->_path);

    if(tl->istxt == 1){
        EraseFile(nwInf->_path);
    }   
    else{

    }
}





char* addMeta(FILE* JsFile,char* PartName,int id,char* name,char* type,char* txt,int owner,int ugo,int fid){

    char* ABSid    = newString(50);
    sprintf(ABSid,"%s#%d",PartName,id);

    char* ABSowner = newString(50);
    sprintf(ABSowner,"%s#%d",PartName,owner);

    char* ABSfid   = newString(50);
    sprintf(ABSfid,"%s#%d",PartName,fid);

    

    
    
    fprintf(JsFile,"\t\t\t\t\t\"id\": \"%s\",\n",ABSid);
    fprintf(JsFile,"\t\t\t\t\t\"name\": \"%s\",\n",name);
    fprintf(JsFile,"\t\t\t\t\t\"type\": \"%s\",\n",type);

    if(strcasecmp(txt,"null") == 0){
        fprintf(JsFile,"\t\t\t\t\t\"txt\": %s,\n",txt);
    }
    else{
        fprintf(JsFile,"\t\t\t\t\t\"txt\": \"%s\",\n",txt);
    }

    if(owner == -1){
        fprintf(JsFile,"\t\t\t\t\t\"owner\": \"%s\",\n","SDisk#SPart#111");
    }
    else{
        if(strcasecmp(name,"users.txt") == 0){
            fprintf(JsFile,"\t\t\t\t\t\"owner\": \"%s\",\n","SDisk#SPart#111");
        }
        else{
            fprintf(JsFile,"\t\t\t\t\t\"owner\": \"%s\",\n",ABSowner);
        }
        
    }
    
    fprintf(JsFile,"\t\t\t\t\t\"ugo\": %d,\n",ugo);

    if(fid == -1){
        fprintf(JsFile,"\t\t\t\t\t\"fid\": %s\n","null");
    }
    else{
        fprintf(JsFile,"\t\t\t\t\t\"fid\": \"%s\"\n",ABSfid);
    }
}

char* addJsFolder(FILE* JsFile,char* PartName,int id,char* name,char* txt,int owner,int ugo,int fid){
    fprintf(JsFile,"\t\t\t\t{\n");
        addMeta(JsFile,PartName,id,name,"folder",txt,owner,ugo,fid);
    fprintf(JsFile,"\t\t\t\t},\n");
}

char* addJsFile(FILE* JsFile,char* PartName,int id,char* name,char* txt,int owner,int ugo,int fid){
    fprintf(JsFile,"\t\t\t\t{\n");
        addMeta(JsFile,PartName,id,name,"file",txt,owner,ugo,fid);
    fprintf(JsFile,"\t\t\t\t},\n");
}

/*
char* getName_By_Inode(int iNode_Bit_ID,int iFather_Bit_ID){
    char* Name = NULL;

    if(iNode_Bit_ID == 0){
        return newString("/");
    }

    Inode* Rt = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");

    int cnt = 0;
    
    //Direct
    while(cnt < 12){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];

        //******* FolderBlock Tour ******
        FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Son_ID_Bit,"FolderBlock");
        int i = 0;
        while(i < 4){
            if(Fb->b_content[i].b_inodo == -1){i++; continue;}

            char* iName  = newString(Fb->b_content[i].b_name);
            int Next_ID_Bit = Fb->b_content[i].b_inodo; 
            char* NextName = getGraphStructName("Inode",Next_ID_Bit);

            if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){
                if(iNode_Bit_ID == Next_ID_Bit){
                    return iName;
                }
            }
            i++;
        }
        cnt++;
    }

    return Name;
}
*/


char* getJsTree(FILE* JsFile,char* PartName,int iNode_Bit_ID){

    //Type 0 ---> Folder
    //Type 1 ---> File

    if(iNode_Bit_ID == 0){
        addJsFolder(JsFile,PartName,0,"/","null",-1,777,-1);
    }

    Inode* Rt = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");

    int cnt = 0;
    
    //Direct
    while(cnt < 12){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];

        //Folder
        if(Rt->i_type == 0){

            //Son Link Name
            char* SonName = getGraphStructName("FolderBlock",Son_ID_Bit);

            //Linking

            //******* FolderBlock Tour ******
            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Son_ID_Bit,"FolderBlock");
            int i = 0;
            while(i < 4){
                if(Fb->b_content[i].b_inodo == -1){i++; continue;}

                char* iName  = newString(Fb->b_content[i].b_name);
                int Next_ID_Bit = Fb->b_content[i].b_inodo; 
                char* NextName = getGraphStructName("Inode",Next_ID_Bit);

                int istxt = Check_If_Is_txtFile(iName);

                if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){

                    Inode* pps = (Inode*)BinLoad_Str(Next_ID_Bit,"Inode");

                    int owner = pps->i_uid;
                    int ugo   = pps->i_perm;

                    if(istxt){
                        char* txtCont = ReadFile_By_iNode(Next_ID_Bit);
                        txtCont = StringCloneWithOut(txtCont,'\n');
                        addJsFile(JsFile,PartName,Next_ID_Bit,iName,txtCont,owner,ugo,iNode_Bit_ID);
                    }
                    else{
                        addJsFolder(JsFile,PartName,Next_ID_Bit,iName,"null",owner,ugo,iNode_Bit_ID);
                        getJsTree(JsFile,PartName,Next_ID_Bit);
                    }
                }
                i++;
            }
        }
        cnt++;
    }
}

void syncronice_do(InfoCatcher* nwInf){

    if(Omni->LoggedUser == NULL){
        setOmni(nwInf->_id);
    }

    char* PartName = Omni->PartBatch_inUse->PartName;
    char* DiskName = Path_Get_FileName(Omni->CompletePathDir_of_Disk_inUse);

    char* BBC = right_chop(newString(DiskName),'.');
    

    char* PartID   = nwInf->_id;

    char* JsPath = newString(500);
    sprintf(JsPath,"JS_%s_%s_%s.json",BBC,PartName,PartID);

    FILE* JsFile = fopen(JsPath,"w");

    sprintf(PartName,"%s#%s",BBC,newString(PartName));

    DoublyGenericList* UsrList = getUsersList();
    DoublyGenericList* GrpList = getGroupsList();


    if(JsFile){

        fprintf(JsFile,"{\n");
            fprintf(JsFile,"\t\"jspartition\":\n");
            fprintf(JsFile,"\t[\n");
                // Header ------------------------------------------------------------
                fprintf(JsFile,"\t\t{\n");
                    fprintf(JsFile,"\t\t\t\"header\":\n");
                    fprintf(JsFile,"\t\t\t{\n");
                        fprintf(JsFile,"\t\t\t\t\"diskname\": \"%s\",\n",BBC);
                        //fprintf(JsFile,"\t\t\t\t\"disksize\": \"%i\",\n",7777);
                        fprintf(JsFile,"\t\t\t\t\"partname\": \"%s\",\n",PartName);
                        fprintf(JsFile,"\t\t\t\t\"mount\": \"%s\"\n",PartID);
                        //fprintf(JsFile,"\t\t\t\t\"partsize\": \"%i\"\n",5555);
                        //fprintf(JsFile,"\t\t\t\t\"partid\": \"%s\"\n",PartID);
                    fprintf(JsFile,"\t\t\t}\n");
                fprintf(JsFile,"\t\t},\n");


                // Users ------------------------------------------------------------
                fprintf(JsFile,"\t\t{\n");
                    fprintf(JsFile,"\t\t\t\"users\":\n");
                    fprintf(JsFile,"\t\t\t[\n");

                    int i = 0;
                    while(UsrList->Length > 0){
                        GroupUserInfo* UserInf = (GroupUserInfo*)DeQueue(UsrList);
                        GroupUserInfo* GroupInf = getGRP_by_Name(UserInf->GrpName,GrpList);

                        if(strcasecmp(UserInf->UsrName,"root") == 0){ i++; continue;}

                            char* usrid = newString(500);
                            char* grpid = newString(500);

                            sprintf(usrid,"%s#%d",PartName,UserInf->ID);
                            sprintf(grpid,"%s#%d",PartName,GroupInf->ID);

                            fprintf(JsFile,"\t\t\t\t\t{\n");
                                fprintf(JsFile,"\t\t\t\t\t\t\"usrid\": \"%s\",\n",usrid);
                                fprintf(JsFile,"\t\t\t\t\t\t\"usrname\": \"%s\",\n",UserInf->UsrName);
                                fprintf(JsFile,"\t\t\t\t\t\t\"usrpassword\": \"%s\",\n",UserInf->Password);
                                
                                fprintf(JsFile,"\t\t\t\t\t\t\"grpid\": \"%s\",\n",grpid);
                                fprintf(JsFile,"\t\t\t\t\t\t\"grpname\": \"%s\"\n",GroupInf->GrpName);
                                if(UsrList->Length == 0){
                                    fprintf(JsFile,"\t\t\t\t\t}\n");
                                }
                                else{
                                    fprintf(JsFile,"\t\t\t\t\t},\n");
                                }
                        i++;
                    }
                    fprintf(JsFile,"\t\t\t]\n");
                fprintf(JsFile,"\t\t},\n");

                // Groups ------------------------------------------------------------
                fprintf(JsFile,"\t\t{\n");
                    fprintf(JsFile,"\t\t\t\"groups\":\n");
                    fprintf(JsFile,"\t\t\t[\n");

                    int j = 0;
                    while(GrpList->Length > 0){

                        GroupUserInfo* GroupInf = (GroupUserInfo*)DeQueue(GrpList);
                        if(strcasecmp(GroupInf->GrpName,"root") == 0){ i++; continue;}


                            char* grpid = newString(500);


                            sprintf(grpid,"%s#%d",PartName,GroupInf->ID);

                            fprintf(JsFile,"\t\t\t\t\t{\n");

                                fprintf(JsFile,"\t\t\t\t\t\t\"grpid\": \"%s\",\n",grpid);
                                fprintf(JsFile,"\t\t\t\t\t\t\"grpname\": \"%s\"\n",GroupInf->GrpName);
                                if(GrpList->Length == 0){
                                    fprintf(JsFile,"\t\t\t\t\t}\n");
                                }
                                else{
                                    fprintf(JsFile,"\t\t\t\t\t},\n");
                                }
                            
                        i++;
                    }

                    fprintf(JsFile,"\t\t\t]\n");
                fprintf(JsFile,"\t\t},\n");

                // JsTree --------------------------------------------------------
                fprintf(JsFile,"\t\t{\n");
                    fprintf(JsFile,"\t\t\t\"jstree\":\n");
                    fprintf(JsFile,"\t\t\t[\n");

                    getJsTree(JsFile,PartName,0);


                    fprintf(JsFile,"\t\t\t]\n");
                fprintf(JsFile,"\t\t}\n");
            fprintf(JsFile,"\t]\n");
        fprintf(JsFile,"}\n");
        fclose(JsFile);
    }



    char* txtCont = getString_from_File(JsPath);
    txtCont = StringCloneWithOut(txtCont,'\n');
    txtCont = StringCloneWithOut(txtCont,'\t');

    int lg = strlen(txtCont);
    txtCont[lg - 5] = ' ';

    char* POST = newString(9000);
    sprintf(POST,"curl -d '%s' -H \"Content-Type: application/json\" -X POST http://localhost:3000/sync",txtCont);
    system(POST);

    if(Omni->LoggedUser == NULL){
        Omni = newGLS();
    } 

}




//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ R E P
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............



void rep_F1_do(InfoCatcher* nwInf){
    Mounted_Part* mP = getPartMounted_By_vID(nwInf->_id);
    
    if(mP == NULL){
        printf("\n");
        printf("REP ERROR: El ID de Montaje   -> %s <-   No Existe\n",nwInf->_id);
        return;
    } 

    char* tmp = nwInf->_path;
    int ln = strlen(tmp);
    tmp[ln - 1] = 't';
    tmp[ln - 2] = 'o';
    tmp[ln - 3] = 'd';

    char* RepName = Path_Get_FileName(newString(nwInf->_path));
    char* RepPath = Path_Get_Isolated(newString(nwInf->_path));

    Locat* lcat = vdTransform(nwInf->_id);
    char*  Disk_Dir = UsingDisk_List[lcat->Letter].CompletePathDir;

    if(strcasecmp(nwInf->_name,"mbr") == 0){
        Generate_MBR_Report(Disk_Dir,RepPath,RepName);
        printf("\n");
        printf("REP SUCCESS: Reporte DISK   -> %s <-   Generado con Exito\n",RepName);
    }
    else if(strcasecmp(nwInf->_name,"disk") == 0){
        GenerateDiskRender(Disk_Dir,RepPath,RepName);
        printf("\n");
        printf("REP SUCCESS: Reporte DISK   -> %s <-   Generado con Exito\n",RepName);
    }
    else{
        printf("\n");
        printf("REP ERROR: Parametro -name   -> %s <-   No Valido\n",nwInf->_name);
        return;
    }
}

void rep_F2_do(InfoCatcher* nwInf){
    //setOmni(nwInf->_id);
    if(strcasecmp(nwInf->_name,"file") == 0){
        Generate_File_Rep(nwInf->_path,nwInf->_ruta);
        //Omni = newGLS();
        return;
    }
    if(strcasecmp(nwInf->_name,"ls") == 0){
        Generate_Ls_Rep(nwInf->_path,nwInf->_ruta);
        //Omni = newGLS();
        return;
    }
    FullViewRender(newString(nwInf->_path),nwInf->_name,nwInf->_id);
    //Omni = newGLS();
}

#endif // F1_DO_H