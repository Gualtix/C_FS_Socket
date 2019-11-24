#ifndef HELPER_H
#define HELPER_H

#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "StringHandler.h"
#include "DoublyGenericList.h"

#define Byte 1
#define Kilo 1024
#define Mega (Kilo * 1024)

typedef struct TheLast{
    char* Name;
    char* Type;
    int istxt;
}TheLast;

TheLast* newTheLast(){

    TheLast* tl = (TheLast*)malloc(sizeof(TheLast));
    
    tl->istxt = 0;
    tl->Name = NULL;
    tl->Type = NULL;

    return tl;
}

char* getDateTime(){
    time_t Tmp = time(0);
    char ShapeDate[20];
    strftime(ShapeDate,128,"%d/%m/%y %H:%M:%S",localtime(&Tmp));
    char* Dt = newString(&ShapeDate[0]);
    return Dt;
}


void Print_Long_Msg(char* CMD,char* Type,char* PreMsg,char* Param,char*PostMsg){
    printf("\n");
    printf("%s %s: %s   -> %s <-   %s\n",CMD,Type,PreMsg,Param,PostMsg);
}


void Print_Msg(char* CMD,char* Type,char* Msg){
    printf("\n");
    printf("%s %s: %s\n",CMD,Type,Msg);
}

DoublyGenericList* PathSeparate(char* CompletePathDir){

    DoublyGenericList* PathList = new_DoublyGenericList();

    char* token;
    char* FileName;

    char* tmp = newString(CompletePathDir);
    token = strtok(tmp,"/");
   
    while(token != NULL ) {        
        EnQueue(PathList,newString(token));
        FileName = newString(token);
        token = strtok(NULL, "/");
    }

    char* pch;
    pch = strchr(FileName,'.');

    //NULL = false = is Folder
    if(pch == NULL){
        EnQueue(PathList,newString("false"));
    }
    //true = is File
    else{
        EnQueue(PathList,newString("true"));
    }

    return PathList;
}

char* Path_Get_Father(char* CompletePathDir){
    DoublyGenericList* PathList = PathSeparate(CompletePathDir);

    if(PathList->Length == 2){
        return newString("/");
    }

    char* Op = (char*)Pop(PathList);
    char* Path;

    char* FileName = (char*)Pop(PathList);

    int nwLn = strlen(CompletePathDir) - strlen(FileName) - 1;
    char* tmp = newString(CompletePathDir);
    tmp[nwLn] = '\0';
    tmp = newString(tmp);
    return tmp;


}

char* Path_Get_Isolated(char* CompletePathDir){

    DoublyGenericList* PathList = PathSeparate(CompletePathDir);
    
    char* Op = (char*)Pop(PathList);
    char* Path;
    char* FileName;

    if(strcmp(Op,"true") == 0){

        FileName = (char*)Pop(PathList);

        int nwLn = strlen(CompletePathDir) - strlen(FileName);
        char* tmp = newString(CompletePathDir);
        tmp[nwLn] = '\0';
        tmp = newString(tmp);
        return tmp;
    }

    if(strcmp(Op,"false") == 0){
        return CompletePathDir;
    }

}

char* Path_Get_FileName(char* CompletePathDir){
    DoublyGenericList* PathList = PathSeparate(CompletePathDir);
    
    char* Op = (char*)Pop(PathList);
    char* Path;
    char* FileName;

    if(strcmp(Op,"true") == 0){
        FileName = (char*)Pop(PathList);
        return FileName;
    }

    if(strcmp(Op,"false") == 0){
        return NULL;
    }

}

char* Path_get_Last_FolderName(char* CompletePathDir){
    DoublyGenericList* PathList = PathSeparate(CompletePathDir);

    char* Op = (char*)Pop(PathList);
    char* Path;
    char* FileName;

    if(strcmp(Op,"true") == 0){
        FileName = (char*)Pop(PathList);
        return FileName;
    }

    if(strcmp(Op,"false") == 0){
        Op = NULL;
        if(PathList->Length > 0){
            Op = (char*)Pop(PathList);
        }
        return Op;
    }
}

/*
char* Path_Get_LastDirName(char* CompletePathDir){
    DoublyGenericList* PathList = PathSeparate(CompletePathDir);
    
    char* Op = (char*)Pop(PathList);
    char* Path;
    char* FileName;
    char* LastDir;

    if(strcmp(Op,"true") == 0){

        FileName = (char*)Pop(PathList);
        LastDir  = (char*)Pop(PathList);
        return LastDir;
    }

    if(strcmp(Op,"false") == 0){
        LastDir  = (char*)Pop(PathList);
        return LastDir;
    }
}
*/

TheLast* getTheLast(char* Path){

    
    TheLast* tl = newTheLast();

    if(strcasecmp(Path,"/") == 0){
        tl->istxt = 0;
        tl->Name = newString("/");
        tl->Type = newString("Folder");
        return tl;
    }

    char* FileName = Path_Get_FileName(Path);
    char* FolderName = Path_get_Last_FolderName(Path);
    if(FileName != NULL){
        tl->istxt = 1;
        tl->Name = FileName;
        tl->Type = newString("Archivo");
    }
    else{
        tl->istxt = 0;
        tl->Name = FolderName;
        tl->Type = newString("Folder");
    }

    return tl;
}

int CalcSize_in_Bytes(int PD_Size,char Unit){

    if(Unit =='b'){
        return PD_Size;
    }
    if(Unit == 'k'){
        return PD_Size * Kilo;
    }
    else if(Unit == 'm'){
        return PD_Size * Mega;
    }
    else{
        return -1;
    }
}

int Validate_If_Path_Exists(char* Path){
    DIR* Test = NULL;
    Test = opendir(Path);
    return Test? 1 : 0;
}

int CreatePathDir(char* Path){

    if(Validate_If_Path_Exists(Path)){
        return 1;
    }

    char NewPath[200];

    // To get Permission on /home
    // sudo chown -R $USER:$USER /home
    snprintf(NewPath,sizeof(NewPath),"mkdir -p -v -m777 \"%s\"",Path);
    system(NewPath);

    return Validate_If_Path_Exists(Path)? 1:0;
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ F 2
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

int Check_If_Is_txtFile(char* Name){

    int Ln = strlen(Name);

    if(Name[Ln - 1] != 't'){
        return 0;
    }
    if(Name[Ln - 2] != 'x'){
        return 0;
    }
    if(Name[Ln - 3] != 't'){
        return 0;
    }
    if(Name[Ln - 4] != '.'){
        return 0;
    }
    return 1;
}

char* Write_JSonFile(char* Path, char* Content){

    char* txtPath = newString(Path);

    char* Type   = newString("json");
    int ln = strlen(txtPath);

    txtPath[ln - 1] = Type[3];
    txtPath[ln - 2] = Type[2];
    txtPath[ln - 3] = Type[1];
    txtPath[ln - 4] = Type[0];


    FILE* Fl = fopen(txtPath,"w");
    if(Fl){
        int results = fputs(Content, Fl);
        fclose(Fl);
    }

}

char* Write_txtFile(char* Path, char* Content){

    char* txtPath = newString(Path);

    char* Type   = newString("txt");
    int ln = strlen(txtPath);

    txtPath[ln - 1] = Type[2];
    txtPath[ln - 2] = Type[1];
    txtPath[ln - 3] = Type[0];


    FILE* Fl = fopen(txtPath,"w");
    if(Fl){
        int results = fputs(Content, Fl);
        fclose(Fl);
    }

}

char* getString_from_File(char* Path){

    FILE* fp = fopen (Path,"rb");
    long lSize;
    char* buffer;

    if(fp){

        //fp = fopen (Path, "rb" );
        //if( !fp ) perror(Path),exit(1);

        fseek(fp,0L,SEEK_END);
        lSize = ftell(fp);
        rewind(fp);

        /* allocate memory for entire content */
        buffer = (char*)calloc( 1, lSize+1 );
        if(!buffer)fclose(fp),fputs("memory alloc fails",stderr),exit(1);

        /* copy the file into the buffer */
        if(1!=fread(buffer,lSize,1,fp))
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

        /* do your work here, buffer is a string contains the whole text */
        fclose(fp);
        //free(buffer);

        return newString(buffer);
    }
    else{
        return NULL;
    }

}

DoublyGenericList* getSubstring_64CharList(char* Content){

    DoublyGenericList* Ls = new_DoublyGenericList();

    // ******* File Content Sharing *******
    int contLen = strlen(Content);
    int Base = 63;
    int nB = (contLen / Base);
    int nR = (contLen % Base);

    int ptr = 0;

    int cnt = 0;
    while(cnt < nB){
        char* str = newString(Base);

        int i = 0;
        while(i < Base){
            str[i] = Content[ptr];
            i++;
            ptr++;
        }

        EnQueue(Ls,str);
        cnt++;
    }

    if(nR > 0){

        int Lm = nR;
        int i = 0;

        char* str = newString(Base);
        memset(str,'\0',sizeof(char) * Base);

        while(i < Lm){
            str[i] = Content[ptr];
            i++;
            ptr++;
        }

        EnQueue(Ls,str);
    }


    if(Ls->Length > 0){
        return Ls;
    }

    return NULL;
}


char* get_DotExt_Path(char* Path){

    char* DotPath = newString(Path);

    char* Type   = newString("dot");
    int ln = strlen(DotPath);

    DotPath[ln - 1] = Type[2];
    DotPath[ln - 2] = Type[1];
    DotPath[ln - 3] = Type[0];
    return DotPath;
}

/*
void Generate_TypeFile_Rep(char* CompleteReportPathDir){


    char* DotPath = get_DotExt_Path(CompleteReportPathDir);

    char* Type = newString(3);
    int ln = strlen(CompleteReportPathDir);

    Type[2] = CompleteReportPathDir[ln - 1];
    Type[1] = CompleteReportPathDir[ln - 2];
    Type[0] = CompleteReportPathDir[ln - 3];

    char* alt = newString(15);

    if(strcasecmp(Type,"png")== 0){
        alt = newString("dot -Tpng ");
        alt = Concat_Izq_with_Der(alt,DotPath,'s','s');
        alt = Concat_Izq_with_Der(alt,newString(" "),'s','s');
        alt = Concat_Izq_with_Der(alt,newString(" -o "),'s','s');
        alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');
    }

    if(strcasecmp(Type,"pdf")== 0){
        alt = newString("dot -Tpdf ");
        alt = Concat_Izq_with_Der(alt,DotPath,'s','s');
        alt = Concat_Izq_with_Der(alt,newString(" "),'s','s');
        alt = Concat_Izq_with_Der(alt,newString(" -o "),'s','s');
        alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');
    }

    system(alt);
}
*/

#endif // HELPER_H