#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *right_trim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *left_trim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char* newString(int Ln){
    // +1 for '\0' character
    char* Str = (char*) malloc((Ln + 1) * sizeof(char)); 
    memset(Str,'^',Ln);
    Str[Ln] = '\0';
    return Str;
}


char* newString(char* Str){
    if(Str == NULL){
        return NULL;
    }
    int Ln = strlen(Str);
    char* Rs = newString(Ln);
    int cnt = 0;
    while(cnt < Ln){
        Rs[cnt] = Str[cnt];
        cnt++;
    }
    return Rs;
}

char* newString(const char* Str){
    int Ln = strlen(Str);
    char* Rs = newString(Ln);
    int cnt = 0;
    while(cnt < Ln){
        Rs[cnt] = Str[cnt];
        cnt++;
    }
    return Rs;
}

char* right_chop(char *str, const char sp){
    int i = 0;
    int n = strlen(str);
    while(i < n){

        if(str[n-1-i] != sp){
            str[n-1-i] = '\0';
        }
        else{
            str[n-1-i] = '\0';
            break;
        }
        i++;
    }

    return newString(str);
}

char* toString(void* _Izq, char It){

    char* Izq = newString(100);

    if(_Izq != NULL){
        //------------ I Z Q
        if(It == 'c'){
            char* tmp = (char*) _Izq;
            Izq = newString(1);
            Izq[0] = tmp[0];
        }

        if(It == 's'){
            Izq = (char*) _Izq;
        }

        if(It == 'i'){
            int *tmp = (int*) _Izq;
            sprintf(Izq,"%d",*tmp);
        }

        if(It == 'd'){
            double* tmp = (double*) _Izq;
            sprintf(Izq,"%0.2f",*tmp);
        }
    }

    if(_Izq == NULL){
        return NULL;
    }

    int Ln = strlen(Izq);
    char* Str = newString(Ln);
    strcpy(Str,Izq);
    return Str;

}

char* Concat_Izq_with_Der(void* _Izq, void* _Der, char It, char Dt){

    char* Izq = newString(100);
    char* Der = newString(100);

    if(_Izq != NULL){
        //------------ I Z Q
        if(It == 'c'){
            char* tmp = (char*) _Izq;
            Izq = newString(1);
            Izq[0] = tmp[0];
        }

        if(It == 's'){
            Izq = (char*) _Izq;
        }

        if(It == 'i'){
            int *tmp = (int*) _Izq;
            sprintf(Izq,"%d",*tmp);
        }

        if(It == 'd'){
            double* tmp = (double*) _Izq;
            sprintf(Izq,"%0.2f",*tmp);
        }
    }

    if(_Der != NULL){
        //------------ D E R
        if(Dt == 'c'){
            char* tmp = (char*) _Der;
            Der = newString(1);
            Der[0] = tmp[0];
        }

        if(Dt == 's'){
            Der = (char*) _Der;
        }

        if(Dt == 'i'){
            int *tmp = (int*) _Der;
            sprintf(Der,"%d",*tmp);
        }

        if(Dt == 'd'){
            double *tmp = (double*) _Der;
            sprintf(Der,"%0.2f",*tmp);
        }
    }

    if(_Izq == NULL){
        return Der;
    }

    if(_Der == NULL){
        return Izq;
    }

    int Ln = strlen(Izq) + strlen(Der);
    char* Str = newString(Ln);
    strcpy(Str,Izq);
    strcat(Str,Der);
    return Str;

}

void String_ByRef_ArrayClear(char** Str){

}

void String_ByRef_AvoidQuotationMarks(char** Str){

}

void String_ByRef_toLower(char** MStr){
    int Ln = strlen(*MStr);
    int cnt = 0;
    while (cnt < Ln) {
        char Current = *(*MStr + cnt);
        *(*MStr + cnt) = putchar(tolower(Current));
        cnt++;
    }
}

int String_IsEmpty(char* MStr){
    int Ln = strlen(MStr);
    int cnt = 0;
    while(cnt < Ln){
        char Tmp = *(MStr + cnt);
        if(Tmp != '^'){
            return 0;
        }
        cnt++;
    }
    return 1;
}

char* StringCloneWithOut(char* SRC,char Sym){

    int Nm = 0;
    char Tmp;

    char* CD = newString(SRC);
    //Destruye la Cadena original
    while ((Tmp = *CD++), ((Tmp == Sym)? ++Nm : 0), Tmp);

    if(Nm == 0){
        return SRC;
    }

    char* Rs = newString(strlen(SRC) - Nm);

    int i = 0;
    int cnt = 0;
    
    while(SRC[cnt] != '\0'){
        if(SRC[cnt] != Sym){
            Rs[i] = SRC[cnt];
            i++;
        }
        cnt++;
    }

    return Rs;
}

int String_isNumber(char* Str){
    int cnt = 0;
    while(Str[cnt] != '\0'){
        if(!isdigit(Str[cnt])){
            return 0;
        }
        cnt++;
    }

    if(atoi(Str) < 0){
        return 0;
    }
    return 1;
}

int String_Has_this_Char(char* Str,char ch){
    
    int ln = strlen(Str);
    
    int i = 0;
    while (i < ln){
        if(Str[i] == ch){
            return i;
        }
        i++;
    }
    
    return - 1;
}

/*
int IsString_a_Number(char* STR){
    int cnt = 0;
    while(STR[cnt] != '\0'){
        if(!isdigit(STR[cnt])){
            return 0;
        }
        cnt++;
    }

    if(atoi(STR) < 0){
        return 0;
    }
    return 1;
}


void StringClearArray(char* STR){
    int cnt = 0;
    int Lm = strlen(STR);
    while(cnt < Lm){
        STR[cnt] = 'w';
        cnt++;
    }
}

void StringClear(char** STR){
    int cnt = 0;
    int Lm = strlen((*STR));
    while(cnt < Lm){
        (*STR)[cnt] = 'w';
        cnt++;
    }
}

void AvoidQuotationMarks(char** STR){

}

char* New_Char_Init_Loaded(char* Cad){


    int Ln = strlen(Cad) + 1;
    int Sz = sizeof(char) * Ln;

    char* Rs = (char*)malloc(Sz);
    //memset(Rs,'/0',Ln);
    int cnt = 0;
    while(cnt < Ln){
        Rs[cnt] = Cad[cnt];
        char P = Cad[cnt];
        cnt++;
    }

    return Rs;

 
}

void String_To_Lower(char** MStr){
    int Ln = strlen(*MStr);
    int cnt = 0;
    while (cnt < Ln) {
        char Current = *(*MStr + cnt);
        *(*MStr + cnt) = putchar(tolower(Current));
        cnt++;
    }
}

int isStringEmpty(char* MStr){
    int Ln = strlen(MStr);
    int cnt = 0;
    while(cnt < Ln){
        char Tmp = *(MStr + cnt);
        if(Tmp != '0'){
            return 0;
        }
        cnt++;
    }
    return 1;
}
char* New_Char_Init(size_t Length){

    int Sz = sizeof(char) * (Length + 1);
    char* RetValue = (char*)malloc(Sz);

    int cnt = 0;

    while(cnt < (Length + 1)){
        *(RetValue + cnt) = '0';
        if(cnt == (Length)){
            *(RetValue + cnt) = '\0';
        }
        cnt++;
    }

    return RetValue;
}

int Get_Char_SizeOf(char* MStr){
    int Ln = strlen(MStr);
    int Sz = sizeof(char) * Ln;
    return Sz;
}

char* ReSize_Char(char* OldChar,int NewLength){
    int Ln = strlen(OldChar);
    char* NewChar = New_Char_Init(NewLength);
    strncpy(NewChar,OldChar,NewLength);
    //free(OldChar);
    return NewChar;
    
}

char* Concat_Izq_With_Der_Char(char* Izq,char* Der){
    int Ln = strlen(Izq) + strlen(Der);
    char* NewChar = New_Char_Init(Ln);
    strcpy(NewChar,Izq);
    strcat(NewChar,Der);
    return NewChar;
}

char* Front_Trim(char* OldChar,int Amount){

    int OldLn = strlen(OldChar);
    int NewLn = (OldLn - Amount);
    char* NewChar = New_Char_Init(NewLn);

    OldLn--;
    NewLn--;

    while(NewLn >= 0){
        *(NewChar + NewLn) = *(OldChar + OldLn);
        NewLn--;
        OldLn--;
    }

    return NewChar;
}

char *End_Trim(char* OldChar,int Amount){
    int Ln = (strlen(OldChar) - Amount);
    char* NewChar = New_Char_Init(Ln);
    strncpy(NewChar,OldChar,Ln);
    return NewChar;
}

char* CloneChar(char* OldChar){
    int OldLn = strlen(OldChar);
    char* NewChar = New_Char_Init(OldLn);
    strcpy(NewChar,OldChar);
    
    return NewChar;
}

char*StringClone(char* SRC){
    int OldLn = strlen(SRC);
    char* NewChar = New_Char_Init(OldLn);
    strcpy(NewChar,SRC);
    return NewChar;
}

char* StringCloneWithOut(char* SRC,char Sym){

    int Nm = 0;
    char Tmp;

    char* CD = StringClone(SRC);
    //Destruye la Cadena original
    while ((Tmp = *CD++), ((Tmp == Sym)? ++Nm : 0), Tmp);

    if(Nm == 0){
        return SRC;
    }

    char* Rs = New_Char_Init(strlen(SRC) - Nm);

    int i = 0;
    int cnt = 0;
    
    while(SRC[cnt] != '\0'){
        if(SRC[cnt] != Sym){
            Rs[i] = SRC[cnt];
            i++;
        }
        cnt++;
    }

    return Rs;
}

void StringMirror(char** STR){

    int cnt = 0;
    int Sz = strlen(*STR);
    char* TMP = New_Char_Init(Sz);
    Sz--;

    while(*((*STR)+cnt) != '\0'){
        TMP[cnt] = *((*STR)+Sz);
        cnt++;
        Sz--;
    }

    // Error ->STR = &TMP;
    *STR = TMP;
    int k = 1;
}
*/


#endif // STRINGHANDLER_H