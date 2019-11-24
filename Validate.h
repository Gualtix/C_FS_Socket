#ifndef VALIDATE_H
#define VALIDATE_H

#include "Container.h"
#include "Belong.h"

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ P R I N T E R
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


void ErrorPrinter(char* CMD,char* MsgType,char* ParamName,char* ParamValue,char* Msg){
    printf("\n");
    printf("%s %s: Parametro: %s   Valor:   -> %s <-   %s\n",CMD,MsgType,ParamName,ParamValue,Msg);
}

void SuccessPrinter(char* CMD,char* MsgType,char* ParamName,char* ParamValue,char* Msg){
    printf("\n");
    printf("%s %s: Parametro: %s   Valor:   -> %s <-   %s\n",CMD,MsgType,ParamName,ParamValue,Msg);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Each
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

int idV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ _id: Mandatory
    if(nwInf->_id ==  NULL){
        ErrorPrinter(CMD,"ERROR","-id","NULL","Es Obligatorio");
        return 0;
    }
    else{
        Mounted_Part* mP = getPartMounted_By_vID(nwInf->_id);
        if(mP == NULL){
            ErrorPrinter(CMD,"ERROR","-id",nwInf->_id,"No es una Particion Montada");
            return 0;
        }
    }
    return 1;
}

int typeV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ _type: Optional
    if(nwInf->_type == NULL){
        nwInf->_type = "full";
        return 1;
    }

    if(strcasecmp(nwInf->_type,"fast") != 0 && strcasecmp(nwInf->_type,"full")){
        nwInf->_type == "full";
        return 1;
    }

    return 1;
}

int fsV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ _fs: Optional
    if(nwInf->_fs == NULL){
        nwInf->_fs = newString("3fs");
        return 1;
    }

    nwInf->_fs = "3fs";

    return 1;
}

int usrV(char* CMD,InfoCatcher* nwInf){


    //(^< ............ ............ ............ ............ ............ _usr: Mandatory
    if(nwInf->_usr ==  NULL){
        ErrorPrinter(CMD,"ERROR","-usr","NULL","Es Obligatorio");
        return 0;
    }
    
    DoublyGenericList* usrList = getUsersList();
    int usr = usrExists(nwInf->_usr,usrList);

    if(strcasecmp(CMD,"CHOWN") == 0){
        if(usr == -1){
            ErrorPrinter(CMD,"ERROR","-usr",nwInf->_usr,"El Usuario No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"CHGRP") == 0){
        if(usr == -1){
            ErrorPrinter(CMD,"ERROR","-usr",nwInf->_usr,"El Usuario No Existe");
            return 0;
        }
        return 1;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ MKUSR
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    if(strcasecmp(CMD,"MKUSR") == 0){
        if(usr > -1){
            ErrorPrinter(CMD,"ERROR","-usr",nwInf->_usr,"El Usuario Ya Existe");
            return 0;
        }
        return 1;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ RMUSR
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    if(strcasecmp(CMD,"RMUSR") == 0){
        if(usr == -1){
            ErrorPrinter(CMD,"ERROR","-usr",nwInf->_usr,"El Usuario No Existe");
            return 0;
        }
        return 1;
    }
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ LOGIN
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    if(strcasecmp(CMD,"LOGIN") == 0){
        if(usr == -1){
        ErrorPrinter(CMD,"ERROR","-usr",nwInf->_usr,"El Usuario no Existe");
        return 0;
        }
        return 1;
    }   
}

int pwdV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ _pwd: Mandatory
    if(nwInf->_pwd ==  NULL){
        ErrorPrinter(CMD,"ERROR","-pwd","NULL","Es Obligatorio");
        return 0;
    }

    DoublyGenericList* usrList = getUsersList();
    GroupUserInfo* gu = getUSR_by_Name(nwInf->_usr,usrList);

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ MKUSR
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    if(strcasecmp(CMD,"MKUSR") == 0){
        return 1;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ LOGIN
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    if(strcasecmp(CMD,"LOGIN") == 0){
        if(strcasecmp(nwInf->_pwd,gu->Password) != 0){
        ErrorPrinter("LOGIN","ERROR","-pwd",nwInf->_pwd,"Password Incorrecto");
            return 0;
        }
        return 1;
    }

    
}

int nameV(char* CMD,InfoCatcher* nwInf){

    //(^< ............ ............ ............ ............ ............ -name: Mandatory
    if(nwInf->_name == NULL){
        ErrorPrinter(CMD,"ERROR","-name","NULL","Es Obligatorio");
        return 0;
    }

    if(strcasecmp(CMD,"FIND") == 0){
        Existence* ex = vFF_Exists(nwInf->_path);
        SeekInfo* sk = CompleteSeeker(ex->iNode,nwInf->_name);
        if(sk == NULL){
            ErrorPrinter(CMD,"ERROR","-name",nwInf->_name,"Este Archivo/Carpeta No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"REN") == 0){
        Existence* ex = vFF_Exists(nwInf->_path);
        SeekInfo* sk = CompleteSeeker(ex->iNodeFather,nwInf->_name);
        if(sk != NULL){
            ErrorPrinter(CMD,"ERROR","-name",nwInf->_name,"Este Nombre ya Existe");
            return 0;
        }
        return 1;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ REP
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    if(strcasecmp(CMD,"REP") == 0){
        if(strcasecmp(nwInf->_name,"inode")      != 0 &&
           strcasecmp(nwInf->_name,"journaling") != 0 &&
           strcasecmp(nwInf->_name,"block")      != 0 &&
           strcasecmp(nwInf->_name,"bm_inode")   != 0 &&
           strcasecmp(nwInf->_name,"bm_block")   != 0 &&
           strcasecmp(nwInf->_name,"tree")       != 0 &&
           strcasecmp(nwInf->_name,"sb")         != 0 &&
           strcasecmp(nwInf->_name,"file")       != 0 &&
           strcasecmp(nwInf->_name,"ls")         != 0
        ){
            ErrorPrinter(CMD,"ERROR","-name",nwInf->_name,"Este Tipo de Reporte no Existe...");
            return 0;
        }
        return 1;
    }

    DoublyGenericList*  grpList = getGroupsList();
    GroupUserInfo* gu = newGrus();
    int grpEx = grpExists(nwInf->_name,grpList);

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ MKGRP
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    
    //(^< ............ ............ ............ ............ ............ -name: Unique
    if(strcasecmp(CMD,"MKGRP") == 0){
        if(grpEx > -1){
            ErrorPrinter(CMD,"ERROR","-name",nwInf->_name,"Este Grupo Ya Existe");
            return 0;
        }
        return 1;
    }
    
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ RMGRP
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    
    //(^< ............ ............ ............ ............ ............ -name: Exist
    if(strcasecmp(CMD,"RMGRP") == 0){
        if(grpEx == -1){
            ErrorPrinter(CMD,"ERROR","-name",nwInf->_name,"Este Grupo No Existe");
            return 0;
        }
        return 1;
    }

    
    
}

int rutaV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ -ruta: Mandatory
    if(strcasecmp(nwInf->_name,"ls") != 0 && strcasecmp(nwInf->_name,"file") != 0){
        return 1;
    }
    if(nwInf->_ruta == NULL && strcasecmp(nwInf->_name,"mbr") != 0 && strcasecmp(nwInf->_name,"disk") != 0){
        ErrorPrinter(CMD,"ERROR","-ruta","NULL","Es Obligatorio");
        return 0;
    }

    //char* tmPath = newString(nwInf->_path);
    //nwInf->_path = nwInf->_ruta;
    Existence* ex = vFF_Exists(nwInf->_ruta);
    //nwInf->_path = tmPath;
    

    if(strcasecmp(nwInf->_name,"file") == 0){
        if(ex->iNode == -1){
            ErrorPrinter(CMD,"ERROR","-ruta",ex->FFName,"El Archivo No Existe");
            return 0;
        }
    }

    if(strcasecmp(nwInf->_name,"ls") == 0){
        if(ex->iNode == -1){
            if(Check_If_Is_txtFile(ex->FFName)){
                ErrorPrinter(CMD,"ERROR","-ruta",ex->FFName,"El Archivo No Existe");
            }
            else{
                ErrorPrinter(CMD,"ERROR","-ruta",ex->FFName,"La Carpeta No Existe");
            }
            return 0;
        }
    }
    return 1;
}

int grpV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ -grp: Mandatory
    if(nwInf->_grp == NULL){
        ErrorPrinter(CMD,"ERROR","-grp","NULL","Es Obligatorio");
        return 0;
    }
    //(^< ............ ............ ............ ............ ............ -grp: Exist
    DoublyGenericList*  grpList = getGroupsList();
    GroupUserInfo* gu = newGrus();
    int grpEx = grpExists(nwInf->_grp,grpList);

    if(grpEx == -1){
        ErrorPrinter(CMD,"ERROR","-grp",nwInf->_grp,"Este Grupo No Existe");
        return 0;
    }
}

int pathV(char* CMD,InfoCatcher* nwInf){
    //(^< ............ ............ ............ ............ ............ -path: Mandatory
    if(nwInf->_path == NULL){
        ErrorPrinter(CMD,"ERROR","-path","NULL","Es Obligatorio");
        return 0;
    }

    if(strcasecmp(CMD,"REP") == 0){
        return 1;
    }

    Existence* ex = vFF_Exists(nwInf->_path);

    if(nwInf->_P != 1){
        if(ex->PrevOk == 0){
            ErrorPrinter(CMD,"ERROR","-path",ex->FFName,"La Carpeta Raiz No Existe");
            return 0;
        }
    }

    if(strcasecmp(CMD,"CHOWN") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",nwInf->_path,"La Direccion para Cambiar Propietario No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"CHMOD") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",nwInf->_path,"La Direccion para Cambiar Permisos No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"FIND") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",nwInf->_path,"La Direccion de Busqueda No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"MV") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",nwInf->_path,"La Direccion de Origen No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"EDIT") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Archivo No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"CAT") == 0){
        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Archivo No Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"REN") == 0){

        if(strcasecmp(nwInf->_path,"/") == 0){
            ErrorPrinter(CMD,"ERROR","-path","/","La Carpeta Root No Puede Cambiar de Nombre");
            return 0;
        }

        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            if(tl->istxt){
                ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Archivo No Existe");
            }
            else{
                ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Folder No Existe");
            }
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"REM") == 0){

        if(strcasecmp(nwInf->_path,"/") == 0){
            ErrorPrinter(CMD,"ERROR","-path","/","La Carpeta Root No Puede ser Eliminada");
            return 0;
        }

        if(ex->iNode == -1){
            TheLast* tl = getTheLast(nwInf->_path);
            if(tl->istxt){
                ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Archivo No Existe");
            }
            else{
                ErrorPrinter(CMD,"ERROR","-path",tl->Name,"El Folder No Existe");
            }
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"MKDIR") == 0){
        if(ex->iNode > -1){
            ErrorPrinter(CMD,"ERROR","-path",ex->FFName,"La Carpeta Ya Existe");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"MKFILE") == 0){
        if(ex->iNode > -1){
            ErrorPrinter(CMD,"ERROR","-path",ex->FFName,"El Archivo Ya Existe");
            return 0;
        }
        return 1;
    }
}

int contV(char* CMD,InfoCatcher* nwInf){

    if(strcasecmp(CMD,"EDIT") == 0){
        if(nwInf->_cont == NULL){
            ErrorPrinter(CMD,"ERROR","-cont",nwInf->_cont,"El Contenido No Puede ser NULL");
            return 0;
        }
        return 1;
    }

    if(strcasecmp(CMD,"MKFILE") == 0){
        //(^< ............ ............ ............ ............ ............ -cont: Optional
        if(nwInf->_cont != NULL){
            char* txtData = getString_from_File(nwInf->_cont);
            if(txtData == NULL){
                if(isRecovery == 0){
                    ErrorPrinter(CMD,"ERROR","-cont",nwInf->_cont,"Archivo No Encontrado");
                }
                return 0;
            }
            nwInf->txtData = txtData;
        }
        else{
            if(isRecovery == 0){
                ErrorPrinter(CMD,"ERROR","-cont",nwInf->_cont,"Archivo No Encontrado");
            }
            return 0;
        }
        return 1;
    }
}

int sizeV(char* CMD,InfoCatcher* nwInf){
    if(strcasecmp(CMD,"MKFILE") == 0){
        if(nwInf->_size < 0){
            if(isRecovery == 0){
                ErrorPrinter(CMD,"ERROR","-size","Negativo","El Parametro -size No puede ser Negativo");
            }
            return 0;
        }else{
            char* txtData = getDefault_txtContent(nwInf->_size);
            nwInf->txtData = txtData;
        }
        return 1;
    }
}

int destV(char* CMD,InfoCatcher* nwInf){

    //(^< ............ ............ ............ ............ ............ -path: Mandatory
    if(nwInf->_dest == NULL){
        ErrorPrinter(CMD,"ERROR","-dest","NULL","Es Obligatorio");
        return 0;
    }

    Existence* ex = vFF_Exists(nwInf->_dest);

    if(strcasecmp(CMD,"MV") == 0){
        if(ex->iNode == -1){
            ErrorPrinter(CMD,"ERROR","-dest",ex->FFName,"La Carpeta Destino No Existe");
            return 0;
        }
        return 1;
    }
}

int ugoV(char* CMD,InfoCatcher* nwInf){
    if(nwInf->_ugo < 0 || nwInf->_ugo > 777){
        ErrorPrinter(CMD,"ERROR","-ugo","","Valor de Permiso Invalido");
        return 0;
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Permissions
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

int permaV(char* CMD,char* usType,char* _perm,char*Act,char* Name){

    if(_perm[0] == '-' && Act[0] != '-' ){
        printf("\n");
        printf("%s ERROR: Permiso   -> Lectura = r <-   en   -> %s <-   El Usuario como: %s, NO Tiene Permiso de de Lectura\n",CMD,Name,usType);
        return 0;
    }

    if(_perm[1] == '-' && Act[1] != '-' ){
        printf("\n");
        printf("%s ERROR: Permiso   -> Escritura = r <-   en   -> %s <-   El Usuario como: %s, NO Tiene Permiso de de Escritura\n",CMD,Name,usType);
        return 0;
    }

    if(_perm[2] == '-' && Act[2] != '-' ){
        printf("\n");
        printf("%s ERROR: Permiso   -> Ejecucion = r <-   en   -> %s <-   El Usuario como: %s, NO Tiene Permiso de de Ejecucion\n",CMD,Name,usType);
        return 0;
    }
    return 1;
    
}

int permissionV(char* CMD,Inode* iN,int Action,char* Name){

    int perm = iN->i_perm;

    /*int Owner = (perm / 100);

    perm = perm - (Owner * 100);
    int Grp   = (perm / 10);

    perm = perm - (Grp * 10);
    int Other = perm;

    */

    char* tS = newString(3);
    sprintf(tS,"%d",perm);
    
    char* _1 = int_to_OctalPerm(tS[0]);
    char* _2 = int_to_OctalPerm(tS[1]);
    char* _3 = int_to_OctalPerm(tS[2]);

    char* Act = int_to_OctalPerm(Action + 48);

    //Is Owner
    if(Omni->LoggedUser->ID == iN->i_uid){
        return permaV(CMD,"PROPIETARIO",_1,Act,Name);
    }

    //Belongs to Group
    if(Omni->LoggedUser->GrpID == iN->i_gid){
        return permaV(CMD,"INTEGRANTE DEL GRUPO",_2,Act,Name);
    }

    //Is Other
    return permaV(CMD,"OTROS",_3,Act,Name);
}

int onSonV(char* CMD,char* Path,int Action){
    if(strcasecmp(Omni->LoggedUser->UsrName,"root") == 0){
        return 1;
    }

    //char* FatherPath = Path_Get_Father(Path);
    TheLast* tl = getTheLast(Path);
    Existence* ex = vFF_Exists(Path);

    Inode* iN = (Inode*)BinLoad_Str(ex->iNode,"Inode");

    return permissionV(CMD,iN,Action,tl->Name);    
}

int onFatherV(char* CMD,char* Path,int Action){
    if(strcasecmp(Omni->LoggedUser->UsrName,"root") == 0){
        return 1;
    }

    char* FatherPath = Path_Get_Father(Path);
    TheLast* tl = getTheLast(FatherPath);
    Existence* ex = vFF_Exists(Path);

    Inode* iN = (Inode*)BinLoad_Str(ex->iNodeFather,"Inode");

    return permissionV(CMD,iN,Action,tl->Name);    
}

int isOwnerV(char* CMD,char* Path,int _R){

    if(strcasecmp(Omni->LoggedUser->UsrName,"root") == 0){
        return 1;
    }

    TheLast* tl = getTheLast(Path);
    Existence* ex = vFF_Exists(Path);

    Inode* iN  = (Inode*)BinLoad_Str(ex->iNode,"Inode");

    if(_R != 1){

        if(iN->i_uid == Omni->LoggedUser->ID){
            return 1;
        }

        if(tl->istxt == 1){
            printf("\n");
            printf("%s ERROR: El Usuario Logeado No es Propietario del Archivo:   -> %s <-\n",CMD,tl->Name);
            return 0;   
        }
        else{
            printf("\n");
            printf("%s ERROR: El Usuario Logeado No es Propietario de la Carpeta:   -> %s <-\n",CMD,tl->Name);
            return 0;   
            
        }
    }

    if(_R == 1 && tl->istxt == 1){
        if(iN->i_uid == Omni->LoggedUser->ID){
            return 1;
        }

        printf("\n");
        printf("%s ERROR: El Usuario Logeado No es Propietario del Archivo:   -> %s <-\n",CMD,tl->Name);
        return 0;   
    }

    if(_R == 1 && tl->istxt == 0){
        if(iN->i_uid == Omni->LoggedUser->ID){
            return 1;
        }
        printf("\n");
        printf("%s ERROR: El Usuario Logeado No es Propietario de la Carpeta Raiz:   -> %s <-\n",CMD,tl->Name);
        return 0;   
        
    }

    return 1;

    /*

    if(_R == 1){
        SeekInfo* nwSi = SuperSeeker(ex->iNode,"distronone");
        while(iList->Length > 0){
            SeekInfo* tmp = (SeekInfo*)DeQueue(iList);
            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(tmp->FB_Bit_ID,"FolderBlock");

            Inode* inn = (Inode*)BinLoad_Str(Fb->b_content[tmp->FB_Index].b_inodo,"Inode");

            if(inn->i_uid != Omni->LoggedUser->ID){
                printf("\n");
                printf("%s ERROR: El Usuario Logeado No es Propietario de:   -> %s <-\n",CMD,Fb->b_content[tmp->FB_Index].b_name);
                return 0;  
            }
        }
        return 1;
    }
    */
}

int inDeepV(char* CMD,char* Path,int Action){

    if(strcasecmp(Omni->LoggedUser->UsrName,"root") == 0){
        return 1;
    }

    TheLast* tl = getTheLast(Path);
    Existence* ex = vFF_Exists(Path);

    Inode* iN  = (Inode*)BinLoad_Str(ex->iNode,"Inode");

    if(tl->istxt == 1){
        int pm = permissionV(CMD,iN,Action,tl->Name);  
        return pm;
    }
    else{

        SeekInfo* nwSi = SuperSeeker(ex->iNode,tl->Name);
        if(iList->Length == 0){
            int pm = permissionV(CMD,iN,Action,tl->Name); 
            return pm;
        }

        int isOk = 1;
        
        while(iList->Length > 0){
            SeekInfo* tmp = (SeekInfo*)DeQueue(iList);
            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(tmp->FB_Bit_ID,"FolderBlock");

            Inode* inn = (Inode*)BinLoad_Str(Fb->b_content[tmp->FB_Index].b_inodo,"Inode");
            char* tname = Fb->b_content[tmp->FB_Index].b_name;

            int am = permissionV(CMD,inn,Action,tname);

            if(am == 0){
                printf("\n");
                printf("%s ERROR: Permiso de Escritura Denegado En:   -> %s <-\n",CMD,tname);  
                isOk = 0;
            }
        }
        return isOk;
    }
}


//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Manager
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


int ErrorManager(InfoCatcher* nwInf,char* CMD){

    // 1 = No Error = Ok
    int mse = 4;

    //MKFS   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MKFS") == 0){
        if(idV("MKFS",nwInf) == 0) return 0;
        typeV("MKFS",nwInf);
        fsV("MKFS",nwInf);
        return 1;
    }

    //LOGIN   ****************************************************************************************************** 
    if(strcasecmp(CMD,"LOGIN") == 0){
        if(usrV("LOGIN",nwInf) == 0) return 0;
        if(pwdV("LOGIN",nwInf) == 0) return 0;
        if(idV("LOGIN",nwInf)  == 0) return 0;
        return 1;
    }

    //REP   ****************************************************************************************************** 
    if(strcasecmp(CMD,"SYNCRONICE") == 0){
        if(idV("SYNCRONICE",nwInf)     == 0) return 0;
        return 1;
    }
    
    //REP   ****************************************************************************************************** 
    if(strcasecmp(CMD,"REP") == 0){
        if(nameV("REP",nwInf) == 0) return 0;
        if(pathV("REP",nwInf) == 0) return 0;
        if(idV("REP",nwInf)     == 0) return 0;
        if(rutaV("REP",nwInf) == 0) return 0;
        return 1;
    }

    //RECOVERY   ****************************************************************************************************** 
    if(strcasecmp(CMD,"RECOVERY") == 0){
        if(Omni->LoggedUser != NULL){
            printf("\n");
            printf("RECOVERY ERROR: Debe hacer Logout para Iniciar la Recuperacion");
        }
        if(idV("RECOVERY",nwInf) == 0) return 0;
        return 1;
    }

    //LOSS   ****************************************************************************************************** 
    if(strcasecmp(CMD,"LOSS") == 0){
        if(Omni->LoggedUser != NULL){
            printf("\n");
            printf("LOSS ERROR: Debe hacer Logout para Simular la Perdida");
        }
        if(idV("LOSS",nwInf) == 0) return 0;
        return 1;
    }

    //MKFILE   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MKFILE") == 0){
        if(pathV("MKFILE",nwInf) == 0) return 0;
        int sizeOk = sizeV("MKFILE",nwInf);
        int contOk = contV("MKFILE",nwInf);
        if(sizeOk == 0 && contOk == 0){
            return 0;
        }
        //if(onFatherV("MKFILE",nwInf->_path,2) == 0) return 0;
        
        return 1;
    }

    //MKDIR   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MKDIR") == 0){
        if(pathV("MKDIR",nwInf) == 0) return 0;
        //if(onFatherV("MKDIR",nwInf->_path,2) == 0) return 0;
        return 1;
    }

    //CAT   ****************************************************************************************************** 
    if(strcasecmp(CMD,"CAT") == 0){
        nwInf->_path = newString(nwInf->_file);
        if(pathV("CAT",nwInf) == 0) return 0;
        //if(onSonV("CAT",nwInf->_file,4) == 0) return 0;
        return 1;
    }

    //REN   ****************************************************************************************************** 
    if(strcasecmp(CMD,"REN") == 0){
        if(pathV("REN",nwInf) == 0) return 0;
        if(nameV("REN",nwInf) == 0) return 0;
        //if(onSonV("REN",nwInf->_path,2) == 0) return 0;
        return 1;
    }

    //EDIT   ****************************************************************************************************** 
    if(strcasecmp(CMD,"EDIT") == 0){
        if(pathV("EDIT",nwInf) == 0) return 0;
        if(contV("EDIT",nwInf) == 0) return 0;
        //if(onSonV("EDIT",nwInf->_path,6) == 0) return 0;
        return 1;
    }

    //MV   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MV") == 0){
        if(pathV("MV",nwInf) == 0) return 0;
        if(destV("MV",nwInf) == 0) return 0;
        return 1;
    }

    //FIND   ****************************************************************************************************** 
    if(strcasecmp(CMD,"FIND") == 0){
        if(pathV("FIND",nwInf) == 0) return 0;
        if(nameV("FIND",nwInf) == 0) return 0;
        return 1;
    }

    //CHMOD   ****************************************************************************************************** 
    if(strcasecmp(CMD,"CHMOD") == 0){
        if(pathV("CHMOD",nwInf) == 0) return 0;
        if(ugoV("CHMOD",nwInf) == 0) return 0;
        //if(isOwnerV("CHMOD",nwInf->_path,nwInf->_R) == 0) return 0;
        return 1;
    }

    //CHOWN   ****************************************************************************************************** 
    if(strcasecmp(CMD,"CHOWN") == 0){
        if(pathV("CHOWN",nwInf) == 0) return 0;
        if(usrV("CHOWN",nwInf) == 0) return 0;
        //if(isOwnerV("CHOWN",nwInf->_path,nwInf->_R) == 0) return 0;
        return 1;
    }

    //REM   ****************************************************************************************************** 
    if(strcasecmp(CMD,"REM") == 0){
        if(pathV("REM",nwInf) == 0) return 0;
        //if(inDeepV("REM",nwInf->_path,2) == 0) return 0;
        return 1;
    }

    //(^< ............ ............ ............ ............ ............ root use only
    if (strcasecmp(Omni->LoggedUser->UsrName,"root") != 0){
        ErrorPrinter(CMD,"ERROR","Usuario",Omni->LoggedUser->UsrName,"Solo root puede usar este Comando");
        return 0;
    }

    //MKGRP   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MKGRP") == 0){
        if(nameV("MKGRP",nwInf) == 0) return 0;
        return 1;
    }

    //RMGRP   ****************************************************************************************************** 
    if(strcasecmp(CMD,"RMGRP") == 0){
        if(nameV("RMGRP",nwInf) == 0) return 0;
        return 1;
    }

    //MKUSR   ****************************************************************************************************** 
    if(strcasecmp(CMD,"MKUSR") == 0){
        if(usrV("MKUSR",nwInf) == 0) return 0;
        if(pwdV("MKUSR",nwInf) == 0) return 0;
        if(grpV("MKUSR",nwInf)     == 0) return 0;

        return 1;
    }

    //RMUSR   ****************************************************************************************************** 
    if(strcasecmp(CMD,"RMUSR") == 0){
        if(usrV("RMUSR",nwInf) == 0) return 0;
        return 1;
    }

    //CHGRP   ****************************************************************************************************** 
    if(strcasecmp(CMD,"CHGRP") == 0){
        if(usrV("CHGRP",nwInf) == 0) return 0;
        if(grpV("CHGRP",nwInf) == 0) return 0;
        return 1;
    }
}


#endif // VALIDATE_H