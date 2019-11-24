#ifndef ANALIZER_H
#define ANALIZER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Fw/DoublyGenericList.h"
#include "Fw/StringHandler.h"
#include "Container.h"
#include "F1_do.h"
#include "Rep/F1_Rep.h"
#include "Rep/F2_Rep.h"
#include "Validate.h"

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ T O O L S
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

int isLogged(char* CMD){

    if(Omni->LoggedUser ==  NULL){
        printf("\n");
        printf("%s ERROR: No Hay Ninguna Sesion Iniciada...\n",CMD);
        return 0;
    }
    return 1;
    
}

void Exec_CMD(DoublyGenericList* CommandList){

    //Abre el Archivo

    char* Prm_Izq = (char*)DeQueue(CommandList);
    char* Prm_Der = (char*)DeQueue(CommandList);

    char* CompletePathDir = Prm_Der;

    FILE * Fl;
    Fl = fopen(CompletePathDir, "r");

    if(Fl != NULL){

        while(feof(Fl) == 0)
        {
            char* CMDLine = newString(200);
            fgets(CMDLine,200, Fl);

            int isEmpty = String_IsEmpty(CMDLine);

            // Si hay un Comentario lo ignora
            CMDLine = left_trim(CMDLine," ");
            CMDLine = left_trim(CMDLine,"\t");
            
            if (CMDLine[0] == '#' || CMDLine[0] == '\r' || CMDLine[0] == '\n' || isEmpty){
                fflush(Fl);
                continue;
            }
            //Eliminando Comentarios a Fin de Linea
            else if(isEmpty == 0){
                int i = strlen(CMDLine) - 1;
                while(i > 0 ){
                    if(CMDLine[i] == '#'){
                        CMDLine[i] = '\0';
                        CMDLine = newString(CMDLine);
                    }
                    i--;
                }
            }

            EnQueue(CommandList,CMDLine);
            fflush(Fl);
        }
        fclose(Fl);
    }

    else {
        printf("EXEC ERROR: Archivo .sh No Encontrado\n");
    }
}

char *CatchCommandLine(){

    char *line = (char *)malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;)
    {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0)
        {
            len = lenmax;
            char *linen = (char *)realloc(linep, lenmax *= 2);

            if (linen == NULL)
            {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ F 1
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void mk_disk_cmd(InfoCatcher* nwInf){
    //Check
    if(nwInf->_fit == NULL){
        nwInf->_fit = newString("FF");
    }

    if(nwInf->_unit == NULL){
        nwInf->_unit = newString("m");
    }
    mkdisk_do(nwInf);
}

void rm_disk_cmd(InfoCatcher* nwInf){
    //Check
    rmdisk_do(nwInf);
}

void unmount_cmd(InfoCatcher* nwInf){
    Mounted_Part* mP = getPartMounted_By_vID(nwInf->_id);
    
    if(mP == NULL){
        printf("\n");
        printf("MOUNT ERROR: El ID de Montaje   -> %s <-   No Existe\n",nwInf->_id);
        return;
    }   

    Locat* lcat = vdTransform(nwInf->_id);

    UsingDisk_List[lcat->Letter].mntList[lcat->Num - 1] = *newMounted_Part();

    printf("\n");
    printf("MOUNT SUCCESS: Particion   -> %s <-   Desmontada con Exito\n",nwInf->_id);
    Print_Mounted_Parts();
    return;
}

void f_disk_cmd(InfoCatcher* nwInf){

    //(^< ............ ............ ............ ............ ............ C H E C K

    //(^< ............ ............ ............ Obligatory
    if(nwInf->_size == NULL && nwInf->_add == -1){
        printf("\n");
        printf("FDISK ERROR: Parametro Obligatorio -size Faltante\n");
        return;
    }

    if(nwInf->_path == NULL){
        printf("\n");
        printf("FDISK ERROR: Parametro Obligatorio -path Faltante\n");
        return;
    }

    if(nwInf->_name == NULL){
        printf("\n");
        printf("FDISK ERROR: Parametro Obligatorio -name Faltante\n");
        return;
    }
    //(^< ............ ............ ............

    //(^< ............ ............ ............ Default
    if(nwInf->_unit == NULL){
        nwInf->_unit = newString("k");
    }

    if(nwInf->_type == NULL){
        nwInf->_type = newString("p");
    }

    if(nwInf->_fit == NULL){
        nwInf->_fit = newString("wf");
    }

    if(nwInf->_unit[0] == 'k'){
        nwInf->_size = nwInf->_size * 1024;
    }
    else{
        nwInf->_size = nwInf->_size * 1024 * 1024;
    }

    //(^< ............ ............ ............

    //(^< ............ ............ ............ BusinessRules
    MBR* Disk = LoadMBR(nwInf->_path);
    char* DiskName = Path_Get_FileName(nwInf->_path);

    if(Disk == NULL){
        printf("\n");
        printf("FDISK ERROR: Disco No Encontrado\n");
        return;
    }

    //(^< ............ ............ ............ Delete
    if(nwInf->_delete != NULL){

        Mounted_Part* mP = getPartMounted_By_Name(nwInf->_name);
    
        if(mP != NULL){

            printf("\n");
            printf("FDISK WARNING: La Particion   -> %s <-   Esta Montada, Desmontando...\n",nwInf->_name);
            char* vID = getvID_by_PartName(nwInf->_name,DiskName);
            if(vID != NULL){
                nwInf->_id = vID;

                printf("\n");
                unmount_cmd(nwInf);

                printf("\n");
                Delete_Part(nwInf,Disk);
            }
            return;
        }

        Delete_Part(nwInf,Disk);
        return;
    }
    //(^< ............ ............ ............
    if(nwInf->_add != 1223556){

        if(nwInf->_add == 0){
            printf("\n");
            printf("FDISK ADD ERROR: 0 no Valido\n");
            return;
        }

        int SD = 0;
        if(nwInf->_unit[0] == 'k'){
            SD = (nwInf->_add * 1024);
        }
        else if(nwInf->_unit[0] == 'm'){
            SD = (nwInf->_add * 1024 * 1024);
        }
        else{
            SD = nwInf->_add;
        }

        if(SD < 0){
            SD = SD * -1;
        }
      
        MBR* Disk = LoadMBR(nwInf->_path);

        //Current
        GeNode* ND = getFull_NodeBatch(nwInf->_path,Disk,nwInf->_name);

        if(ND == NULL){
            printf("\n");
            printf("FDISK ADD ERROR: La Particion   ->%s<-   No Existe dentro del Disco\n",nwInf->_name);
            return;
        }

        //Current
        Batch* Current = (Batch*)(ND->Dt);

        //Prev
        //Batch* Prev = (Batch*)(ND->Previous->Dt);

        //Next
        Batch* Next  = NULL;
        if(ND->Next != NULL){
            Next = (Batch*)(ND->Next->Dt);
        }

        if(nwInf->_add < 0){
            if(SD >= Current->Size){
                printf("\n");
                printf("FDISK ADD ERROR: El Espacio a Reducir es Mayor que la Particion\n");
                return;
            }

            // R E D U C I R
            if(Current->Type == 'p' || Current->Type == 'e'){
                int index = MBRPartArray_GetIndex_By_PartName(Disk,nwInf->_name);
                Disk->mbr_partition[index].part_size -= SD; 
                UpdateMBR(nwInf->_path,Disk);
                printf("\n");
                printf("FDISK ADD SUCCESS: Particion Reducida Exitosamente\n");
                return;
            }
            if(Current->Type == 'q'){
                EBR* eB = LoadEBR(nwInf->_path,Current->StartByte);
                eB->part_size -= SD;
                UpdateEBR(eB,nwInf->_path);
                printf("\n");
                printf("FDISK ADD SUCCESS: Particion Logica Reducida Exitosamente\n");
                return;
            }
            
        }
        else{
            if(Next == NULL){
                printf("\n");
                printf("FDISK ADD ERROR: No Existe Espacio Libre Junto a la Particion\n");
                return;
            }
            else{
                if(Next->Type != 's'){
                    printf("\n");
                    printf("FDISK ADD ERROR: No Existe Espacio Libre Junto a la Particion\n");
                    return;
                }
            }

            if(SD > Next->Size){
                printf("\n");
                printf("FDISK ADD ERROR: El Espacio Disponible Junto a la Particion no es Suficiente\n");
                return;
            }

            //A U M E N T A R
            if(Current->Type == 'p' || Current->Type == 'e'){
                int index = MBRPartArray_GetIndex_By_PartName(Disk,nwInf->_name);
                Disk->mbr_partition[index].part_size += SD; 
                UpdateMBR(nwInf->_path,Disk);
                printf("\n");
                printf("FDISK ADD SUCCESS: Particion Aumentada Exitosamente\n");
                return;
            }
            if(Current->Type == 'q'){
                EBR* eB = LoadEBR(nwInf->_path,Current->StartByte);
                eB->part_size += SD;
                UpdateEBR(eB,nwInf->_path);
                printf("\n");
                printf("FDISK ADD SUCCESS: Particion Logica Aumentada Exitosamente\n");
                return;
            }

        }
    }
    
    //(^< ............ ............ ............

    int nPrimary  = MBRPartArray_PrimaryCounter(Disk);
    int nExtended = MBRPartArray_ExtendedCounter(Disk);

    int Sum = nPrimary + nExtended;

    if(nExtended > 0 && nwInf->_type[0] == 'e'){
        printf("\n");
        printf("FDISK ERROR: Ya Existe una Particion Extendida\n");
        return;
    }

    if(nExtended == 0 && nwInf->_type[0] == 'l'){
        printf("\n");
        printf("FDISK ERROR: No Existe Particion Extendida para Crear Particion Logica\n");
        return;
    }

    if(Sum == 4 && nwInf->_type[0] != 'l'){
        printf("\n");
        printf("FDISK ERROR: Ya Existen 4 Particiones Titulares\n");
        return;
    }

    //int NameExists = MBRPartArray_PartNameExists(Disk,nwInf->_name);
    Batch* Nm = getBatch_By_PartName(nwInf->_path,Disk,nwInf->_name);
            
    if(Nm != NULL){
        printf("\n");
        printf("FDISK ERROR: El Nombre de la Particion   -> %s <-   ya Existe\n",nwInf->_name);
        return;
    }

    //(^< ............ ............ ............

    
    //(^< ............ ............ ............ ............ ............ D O
    
    fdisk_do(nwInf,Disk);

}

void rep_cmd(InfoCatcher* nwInf){
    if(Omni->LoggedUser == NULL){
        setOmni(nwInf->_id);
    }
    
    if(ErrorManager(nwInf,"REP") == 1){
        if(strcasecmp(nwInf->_name,"mbr") != 0 && strcasecmp(nwInf->_name,"disk") != 0){
            rep_F2_do(nwInf);
        }
        else{
            rep_F1_do(nwInf);
        }
        char* RepName = Path_Get_FileName(nwInf->_path);
        printf("\n");
        printf("REP SUCCESS: Reporte:   -> %s <-   Generado con Exito\n",RepName);
    }
    if(Omni->LoggedUser == NULL){
        Omni = newGLS();
    }   
}

void mount_cmd(InfoCatcher* nwInf){

    
    MBR* Disk = LoadMBR(nwInf->_path);

    if(Disk == NULL){
        printf("\n");
        printf("MOUNT ERROR: Disco   -> %s <-   , NO Encontrado\n",nwInf->_name);
        return;
    }

    Batch* Part = getBatch_By_PartName(nwInf->_path,Disk,nwInf->_name);

    if(Part == NULL){
        printf("\n");
        printf("MOUNT ERROR: La Particion   -> %s <-   No Existe\n",nwInf->_name);
        return;
    }

    Mounted_Part* mP = getPartMounted_By_Name(nwInf->_name);
    
    if(mP != NULL){
        printf("\n");
        printf("MOUNT ERROR: La Particion   -> %s <-   Ya esta Montada\n",nwInf->_name);
        return;
    }
    

    char* mID = get_MountedPart_String_ID(nwInf->_path,nwInf->_name);
    Locat* lcat = vdTransform(mID);

    Mounted_Part* nw_mP = newMounted_Part();
    nw_mP->status = 1;
    nw_mP->ParName = newString(nwInf->_name);
    nw_mP->index = lcat->Num - 1;

    Disk_in_Use* dI = get_Disk_in_Use_By_DiskName(nwInf->_path);

    if(dI == NULL){
        dI = newDisk_in_Use();
        dI->status = 1;
        dI->index = lcat->Letter;
        dI->CompletePathDir = newString(nwInf->_path);
        dI->mntList[lcat->Num - 1] = *nw_mP;
        UsingDisk_List[lcat->Letter] = *dI;
    }
    else{
        dI->mntList[lcat->Num - 1] = *nw_mP;
    }

    printf("\n");
    printf("MOUNT SUCCESS: Particion   -> %s <-   Montada con Exito: ID = %s\n",nwInf->_name,mID);   
    Print_Mounted_Parts(); 

}



//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ P H A S E S
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


int ScanF1(char* Bf,InfoCatcher* nwInf){

    if(strcasecmp(Bf, "mkdisk") == 0){
        mk_disk_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "rmdisk") == 0){
        rm_disk_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "fdisk") == 0){
        f_disk_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "rep") == 0){
        rep_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "mount") == 0){
        mount_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "unmount") == 0){
        unmount_cmd(nwInf);
        return 0;
    }
    else if(strcasecmp(Bf, "pause") == 0){
        getchar();
        return 0;
    }
    return 1;
}

int ScanF2(char* Bf,InfoCatcher* nwInf){

    if (!strcasecmp(Bf, "MKFS")){
        if(ErrorManager(nwInf,"MKFS") == 1){
            mkfs_do(nwInf);
            char* PartName = (getPartMounted_By_vID(nwInf->_id))->ParName;
            printf("\n");
            printf("MKFS SUCCESS: Particion:   -> %s <-   ID:   -> %s <-   Formateada Exitosamente por %s\n",PartName,nwInf->_id,nwInf->_fs);
        }
        return 0;
    }

    if (strcasecmp(Bf, "LOGIN") == 0){
        if(Omni->LoggedUser !=  NULL){
            printf("\n");
            printf("LOGIN ERROR: Ya Hay Una Sesion Iniciada...\n");
            return 0;
        }

        setOmni(nwInf->_id);
        if(ErrorManager(nwInf,"LOGIN") == 1){
            login_do(nwInf);
            if(isRecovery == 0){
                AddJournal("LOGIN",COMMS,664,"users.txt","Archivo");
                Print_Msg("LOGIN","SUCCESS","Sesion Iniciada Exitosamente");
            }
        }

        return 0;
    }

    if (strcasecmp(Bf, "LOSS") == 0){
        if(ErrorManager(nwInf,"LOSS") == 1){
            loss_do(nwInf);
            printf("\n");
            printf("LOSS SUCCESS: Simulacion de Perdida Sobre   -> %s <-   Realizada Exitosamente\n",nwInf->_id);
        }
        return 0;
    }

    //(^< ............ ............ ............ Login Needed
    
    if(isLogged(Bf) == 0) return 0;

    if (strcasecmp(Bf, "LOGOUT") == 0){
        if(isRecovery == 0){
            AddJournal("LOGOUT",COMMS,664,"users.txt","Archivo");
            Print_Msg("LOGOUT","SUCCESS","Sesion Cerrada Exitosamente");
        }
        Omni = newGLS();
        return 0;
    }

    if (strcasecmp(Bf, "MKGRP") == 0){
        if(ErrorManager(nwInf,"MKGRP") == 1){
            mkgrp_do(nwInf);
            if(isRecovery == 0){
                AddJournal("MKGRP",COMMS,664,"users.txt","Archivo");
                Print_Long_Msg("MKGRP","SUCCESS","Grupo",nwInf->_name,"Creado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "RMGRP") == 0){
        if(ErrorManager(nwInf,"RMGRP") == 1){
            rmgrp_do(nwInf);
            if(isRecovery == 0){
                AddJournal("RMGRP",COMMS,664,"users.txt","Archivo");
                Print_Long_Msg("RMGRP","SUCCESS","Grupo",nwInf->_name,"Eliminado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "MKUSR") == 0){
        if(ErrorManager(nwInf,"MKUSR") == 1){
            mkusr_do(nwInf);
            if(isRecovery == 0){
                AddJournal("MKUSR",COMMS,664,"users.txt","Archivo");
                Print_Long_Msg("MKUSR","SUCCESS","Usuario",nwInf->_usr,"Creado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "RMUSR") == 0){
        if(ErrorManager(nwInf,"RMUSR") == 1){
            rmusr_do(nwInf);
            if(isRecovery == 0){
                AddJournal("RMUSR",COMMS,664,"users.txt","Archivo");
                Print_Long_Msg("RMUSR","SUCCESS","Usuario",nwInf->_usr,"Eliminado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "MKDIR") == 0){
        if(ErrorManager(nwInf,"MKDIR") == 1){
            mkdir_do(nwInf);
            if(isRecovery == 0){
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                AddJournal("MKDIR",COMMS,664,FolderName,"Folder");
                Print_Long_Msg("MKDIR","SUCCESS","Directorio",FolderName,"Creado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "MKFILE") == 0){
        if(ErrorManager(nwInf,"MKFILE") == 1){
            mkfile_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                AddJournal("MKFILE",COMMS,664,FileName,"Archivo");
                Print_Long_Msg("MKFILE","SUCCESS","Archivo",FileName,"Creado Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "CAT") == 0){
        if(ErrorManager(nwInf,"CAT") == 1){
            cat_do(nwInf);
        }
        return 0;
    }

    if (strcasecmp(Bf, "CHMOD") == 0){
        if(ErrorManager(nwInf,"CHMOD") == 1){
            chmod_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                if(FileName != NULL){
                    Print_Long_Msg("CHMOD","SUCCESS","Archivo",FileName,"Permisos Modificados Exitosamente");
                    AddJournal("CHMOD",COMMS,664,FileName,"Archivo");
                }
                else{
                    Print_Long_Msg("CHMOD","SUCCESS","Folder",FolderName,"Permisos Modificados Exitosamente");
                    AddJournal("CHMOD",COMMS,664,FolderName,"Folder");
                }
                
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "REM") == 0){
        if(ErrorManager(nwInf,"REM") == 1){
            rem_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                if(FileName != NULL){
                    Print_Long_Msg("REM","SUCCESS","Archivo",FileName,"Eliminado Exitosamente");
                    AddJournal("REM",COMMS,664,FileName,"Archivo");
                }
                else{
                    Print_Long_Msg("REM","SUCCESS","Folder",FolderName,"Eliminado Exitosamente");
                    AddJournal("REM",COMMS,664,FolderName,"Folder");
                }
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "EDIT") == 0){
        if(ErrorManager(nwInf,"EDIT") == 1){
            edit_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                AddJournal("EDIT",COMMS,664,FileName,"Archivo");
                Print_Long_Msg("EDIT","SUCCESS","Archivo",FileName,"Editado Exitosamente");
            }
            
        }
        return 0;
    }

    if(strcasecmp(Bf, "REN") == 0){
        if(ErrorManager(nwInf,"REN") == 1){
            ren_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                if(FileName != NULL){
                    Print_Long_Msg("REN","SUCCESS","Archivo",FileName,"Renombrado Exitosamente");
                    AddJournal("REN",COMMS,664,FileName,"Archivo");
                }
                else{
                    Print_Long_Msg("REN","SUCCESS","Folder",FolderName,"Renombrado Exitosamente");
                    AddJournal("REN",COMMS,664,FolderName,"Folder");
                }
                
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "CP") == 0){
        return 0;
    }

    if (strcasecmp(Bf, "MV") == 0){
        if(ErrorManager(nwInf,"MV") == 1){
            mv_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                if(FileName != NULL){
                    Print_Long_Msg("MV","SUCCESS","Archivo",FileName,"Movido Exitosamente");
                    AddJournal("MV",COMMS,664,FileName,"Folder");
                }
                else{
                    Print_Long_Msg("MV","SUCCESS","Folder",FolderName,"Movido Exitosamente");
                    AddJournal("MV",COMMS,664,FolderName,"Folder");
                }
                
            }
        }

        return 0;
    }

    if (strcasecmp(Bf, "CHOWN") == 0){
        if(ErrorManager(nwInf,"CHOWN") == 1){
            chown_do(nwInf);
            if(isRecovery == 0){
                char* FileName = Path_Get_FileName(nwInf->_path);
                char* FolderName = Path_get_Last_FolderName(nwInf->_path);
                if(FileName != NULL){
                    Print_Long_Msg("CHOWN","SUCCESS","Archivo",FileName,"Propietario Cambiado Exitosamente");
                    AddJournal("CHOWN",COMMS,664,FileName,"Archivo");
                }
                else{
                    Print_Long_Msg("CHOWN","SUCCESS","Folder",FolderName,"Propietario Cambiado Exitosamente");
                    AddJournal("CHOWN",COMMS,664,FolderName,"Folder");
                }
                
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "CHGRP") == 0){
        if(ErrorManager(nwInf,"CHGRP") == 1){
            chgrp_do(nwInf);
            if(isRecovery == 0){
                AddJournal("CHGRP",COMMS,664,"users.txt","Archivo");
                Print_Long_Msg("CHGRP","SUCCESS","Usuario",nwInf->_usr,"El Usuario Ha Cambiado de Grupo Exitosamente");
            }
        }
        return 0;
    }

    if (strcasecmp(Bf, "FIND") == 0){
        if(ErrorManager(nwInf,"FIND") == 1){
            find_do(nwInf);
        }
        return 0;
    }

    if (strcasecmp(Bf, "SYNCRONICE") == 0){
        if(ErrorManager(nwInf,"SYNCRONICE") == 1){
            syncronice_do(nwInf);
        }
        return 0;
    }

    
   return 1;
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ R E C O V E R Y
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void recovery_do(InfoCatcher* nwInf){

    setOmni(nwInf->_id);
    isRecovery = 1;

    clear_blockBits();
    clear_inodeBits();
    Load_Defaut_txt(newInfoCatcher());

    int Jr_StartByte = Omni->PartBatch_inUse->StartByte + sizeof(SuperBlock);

    int iN = Omni->SBinuse->s_inodes_count;
    int i = 0;

    while(i < iN){
        int index = Jr_StartByte + (i * sizeof(Journaling));
        Journaling* tmp = (Journaling*)BinLoad_Str(index,"Journaling");
        if(tmp->isOccupied == '0' || tmp->isOccupied != '1'){
            break;
        }

        char* CMD   = newString(tmp->CMD);
        char* Param = newString(tmp->Content);
        if(strcasecmp(Param,"mv -path~:~/home/wrm/Desktop/a1.txt -dest~:~/home/wrm") == 0){
            int aa = 8;
        }
        
        if(tmp->isOccupied != '0'){
            DoublyGenericList* CommandList = new_DoublyGenericList();
            Param = StringCloneWithOut(Param,'\n');
            FillCommandListTwo(newString(Param),CommandList);
            InfoCatcher* tinf = newInfoCatcher();
            fillInfoCatcher(CommandList,&tinf);
            ScanF2(CMD,tinf);
        }
        if(strcasecmp(CMD,"logout") == 0) setOmni(nwInf->_id);

        i++;
    }
    Omni = newGLS();
    isRecovery = 0;

}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ A N A L I T I C S
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


void ExecuteComand(char *InputString){

    //system("clear");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("CommandLine->   %s\n",InputString);

    if (*(InputString) == '\n'){
        return;
    }

    if(strcasecmp(InputString,"mkgrp -name=\"Compi2\"\n") == 0){
        int kis = 0;
    }

    InputString = StringCloneWithOut(InputString,'\t');
    InputString = StringCloneWithOut(InputString,'\r');
    InputString = StringCloneWithOut(InputString,'\"');
    InputString = StringCloneWithOut(InputString,'\'');
    InputString = StringCloneWithOut(InputString,'\n');
    

    if(strcasecmp(InputString, "Exit\n") == 0){
        printf("\n");
        printf("Saliendo de la APP...\n");
        return;
    }

    DoublyGenericList* CommandList = new_DoublyGenericList();

    char* Main_CMD = strtok(InputString, " ");
    int unknownCMD = 1;
    FillCommandList(Main_CMD,CommandList);

    // T E M P ----
    DoublyGenericList* tmpCL = new_DoublyGenericList();
    int i = 0;
    while(i < CommandList->Length){
        char* tmp = (char*)getNodebyIndex(CommandList,i)->Dt;
        EnQueue(tmpCL,tmp);
        i++;
    }
    // ------------

    InfoCatcher* nwInf = newInfoCatcher();
    fillInfoCatcher(tmpCL,&nwInf);

    if (strcasecmp(Main_CMD, "RECOVERY") == 0){
        if(ErrorManager(nwInf,"RECOVERY") == 1){
            recovery_do(nwInf);
            printf("\n");
            printf("Recovery SUCCESS: Recuparacion de la Particion -> %s <- Generada con Exito\n",nwInf->_id);
        }
        return;
    }

    unknownCMD = ScanF1(Main_CMD,nwInf);

    if(unknownCMD != 0 && strcasecmp(Main_CMD,"exec") != 0){
        unknownCMD = ScanF2(Main_CMD,nwInf);
    }
    
    if(unknownCMD != 0){
        if (strcasecmp(Main_CMD,"Exec") == 0){        
            Exec_CMD(CommandList);
            while (CommandList->Length > 0)
            {
                char* NewCommand = (char*)DeQueue(CommandList);
                COMMS = newString(NewCommand);
                COMMS = StringCloneWithOut(COMMS,'\"');
                COMMS = StringCloneWithOut(COMMS,'\t');
                COMMS = StringCloneWithOut(COMMS,'\n');
                COMMS = StringCloneWithOut(COMMS,'\r');
                COMMS = StringCloneWithOut(COMMS,'\'');
                ExecuteComand(NewCommand);
            }   
        }
        else{
            printf("\n");
            printf("Analizer ERROR: Comando: %s No Reconocido\n", Main_CMD);
        }
    }
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

}


#endif // ANALIZER_H
