#ifndef F2_REP
#define F2_REP

#include "../Fw/Helper.h"
#include "../Fw/StringHandler.h"

#include "../Glovs.h"
#include "../Analizer.h"
#include "../Belong.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

InfoCatcher* fillInfoCatcher(DoublyGenericList* CommandList,InfoCatcher** nwInf){

    char* Prm_Izq = NULL;
    char* Prm_Der = NULL;

    while(CommandList->Length > 0){

        Prm_Izq = (char*)DeQueue(CommandList);
        Prm_Der = (char*)DeQueue(CommandList);

        if(strcasecmp(Prm_Izq,"-path")  != 0 && 
           strcasecmp(Prm_Izq,"-name")  != 0 && 
           strcasecmp(Prm_Izq,"-usr")   != 0 && 
           strcasecmp(Prm_Izq,"-pwd")   != 0 && 
           strcasecmp(Prm_Izq,"-cont")  != 0 && 
           strcasecmp(Prm_Izq,"-ruta")  != 0 &&
           strcasecmp(Prm_Izq,"-grp")   != 0 &&
           strcasecmp(Prm_Izq,"-file")  != 0
        ){
            if(Prm_Der != NULL){
                String_ByRef_toLower(&Prm_Der);
            }
        }

        //(^< ............ ............ ............   _size
        if(strcasecmp(Prm_Izq,"-size") == 0){
            int Nm = atoi(Prm_Der);
            (*nwInf)->_size =  atoi(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _ugo
        if(strcasecmp(Prm_Izq,"-ugo") == 0){
            int Nm = atoi(Prm_Der);
            (*nwInf)->_ugo =  atoi(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _fit
        if(strcasecmp(Prm_Izq,"-fit") == 0){
            (*nwInf)->_fit = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _unit
        if(strcasecmp(Prm_Izq,"-unit") == 0){
            (*nwInf)->_unit = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _path
        if(strcasecmp(Prm_Izq,"-path") == 0){
            (*nwInf)->_path = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _type
        if(strcasecmp(Prm_Izq,"-type") == 0){
            (*nwInf)->_type = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _delete
        if(strcasecmp(Prm_Izq,"-delete") == 0){
            (*nwInf)->_delete = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _add
        if(strcasecmp(Prm_Izq,"-add") == 0){
            int Nm = atoi(Prm_Der);
            (*nwInf)->_add =  atoi(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _name
        if(strcasecmp(Prm_Izq,"-name") == 0){
            (*nwInf)->_name = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _id
        if(strcasecmp(Prm_Izq,"-id") == 0){
            (*nwInf)->_id = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _fs
        if(strcasecmp(Prm_Izq,"-fs") == 0){
            (*nwInf)->_fs = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _usr
        if(strcasecmp(Prm_Izq,"-usr") == 0){
            (*nwInf)->_usr = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _pwd
        if(strcasecmp(Prm_Izq,"-pwd") == 0){
            (*nwInf)->_pwd = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _grp
        if(strcasecmp(Prm_Izq,"-grp") == 0){
            (*nwInf)->_grp= newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _P
        if(!strcasecmp(Prm_Izq,"-P")){
            (*nwInf)->_P = 1;
            if(Prm_Der != NULL){
                FrontInsert(CommandList,Prm_Der);
            }
            continue;
        }

        //(^< ............ ............ ............   _R
        if(!strcasecmp(Prm_Izq,"-R")){
            (*nwInf)->_R = 1;
            if(Prm_Der != NULL){
                FrontInsert(CommandList,Prm_Der);
            }
            continue;
        }

        //(^< ............ ............ ............   _cont
        if(!strcasecmp(Prm_Izq,"-cont")){
            (*nwInf)->_cont = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _ruta
        if(!strcasecmp(Prm_Izq,"-ruta")){
            (*nwInf)->_ruta = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _file
        if(!strcasecmp(Prm_Izq,"-file")){
            (*nwInf)->_file = newString(Prm_Der);
            continue;
        }

        //(^< ............ ............ ............   _dest
        if(!strcasecmp(Prm_Izq,"-dest")){
            (*nwInf)->_dest = newString(Prm_Der);
            continue;
        }
    }
}

void FillCommandList(char* Bf,DoublyGenericList* CommandList){
    int a = 3;
    while(1){
        Bf = strtok(NULL," =");
        if(Bf == NULL){
            break;
        }
        EnQueue(CommandList,Bf);
    }    
}

void FillCommandListTwo(char* Pert,DoublyGenericList* CommandList){
    Pert = strtok(Pert," =");
    while(1){
        Pert = strtok(NULL," =");
        if(Pert == NULL){
            break;
        }
        EnQueue(CommandList,Pert);
    }    
}

void Add_Div(FILE* DotFl){
    fprintf(DotFl,"\t\t\t\t<TR>\n");
        fprintf(DotFl,"\t\t\t\t\t<TD width = \"150\" colspan=\"2\">\n");
            fprintf(DotFl,"\t\t\t\t\t\t*** *** *** *** *** ***<br/>\n");
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    fprintf(DotFl,"\t\t\t\t</TR>\n");
}

void AddSuper(FILE* DotFl,char* Color,char* TopTittle,int ColSpan){
    fprintf(DotFl,"\t\t\t\t\t\t<TR> <TD BGCOLOR = \"%s\" width = \"150\" colspan = \"%d\">- %s -<br/></TD></TR>\n",Color,ColSpan,TopTittle);
}

void AddTwinRow(FILE* DotFl,char* Type,char* Value,char* Color){
    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD BGCOLOR = \"%s\">%s</TD><TD BGCOLOR = \"%s\">%s</TD></TR>\n",Color,Type,Color,Value);
}

void AddRow(FILE* DotFl,char* Type,char* Value){
    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD>%s</TD><TD>%s</TD></TR>\n",Type,Value);
}

void SuperBlockDot(FILE* DotFl){

    char* tS = newString(20);
    
    fprintf(DotFl,"\t\t\tSuperBlock\n");
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#79a6d2","SuperBlock",2);
                AddRow(DotFl,"Name","Value");

                sprintf(tS, "%d",Omni->SBinuse->s_filesystem_type);
                AddRow(DotFl,"s_filesystem_type",tS);
                
                sprintf(tS, "%d",Omni->SBinuse->s_inodes_count);
                AddRow(DotFl,"s_inodes_count",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_blocks_count);
                AddRow(DotFl,"s_blocks_count",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_free_blocks_count);
                AddRow(DotFl,"s_free_blocks_count",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_free_inodes_count);
                AddRow(DotFl,"s_free_inodes_count",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_mtime);
                AddRow(DotFl,"s_mtime",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_umtime);
                AddRow(DotFl,"s_umtime",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_mnt_count);
                AddRow(DotFl,"s_mnt_count",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_magic);
                AddRow(DotFl,"s_magic",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_inode_size);
                AddRow(DotFl,"s_inode_size",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_block_size);
                AddRow(DotFl,"s_block_size",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_first_ino);
                AddRow(DotFl,"s_first_ino",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_first_blo);
                AddRow(DotFl,"s_first_blo",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_bm_inode_start);
                AddRow(DotFl,"s_bm_inode_start",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_bm_block_start);
                AddRow(DotFl,"s_bm_block_start",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_inode_start);
                AddRow(DotFl,"s_inode_start",tS);

                sprintf(tS, "%d",Omni->SBinuse->s_block_start);
                AddRow(DotFl,"s_block_start",tS);
                
            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
        fprintf(DotFl,"\t\t\t]\n");
}

void inodeBitMapDot(FILE* DotFl,int iN){
    
    char* tS = newString(20);
    
    fprintf(DotFl,"\t\tInodeBitMap\n");
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#ff8080\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#ff3333",":: InodeBitMap ::",20);

                int extra = (iN % 20);
                int nRow =  iN - extra;

                int cnt = 0;
                char ch;
                while(cnt < nRow){

                    if(cnt % 20 == 0 ){
                        fprintf(DotFl,"\t\t\t\t\t\t<TR>\n");
                        fprintf(DotFl,"\t\t\t\t\t\t\t");
                    }

                    ch = BinRead_SingleChar(Omni->SBinuse->s_bm_inode_start + cnt);
                    fprintf(DotFl,"<TD>%c</TD>",ch);

                    if( (cnt + 1) >= 5 && (cnt + 1) % 5 == 0 ){
                        fprintf(DotFl,"\n");
                        fprintf(DotFl,"\t\t\t\t\t\t\t");
                    }

                    if( (cnt + 1) >= 20 && (cnt + 1) % 20 == 0 ){
                        fprintf(DotFl,"</TR>\n");
                    }
                    cnt++;
                }

                if(extra > 0){
                    fprintf(DotFl,"\t\t\t\t\t\t<TR>\n");
                    fprintf(DotFl,"\t\t\t\t\t\t\t");

                    while(cnt < iN){
                        ch = BinRead_SingleChar(Omni->SBinuse->s_bm_inode_start + cnt);
                        fprintf(DotFl,"<TD>%c</TD>",ch);
                        if( (cnt + 1) >= 5 && (cnt + 1) % 5 == 0 ){
                            fprintf(DotFl,"\n");
                            fprintf(DotFl,"\t\t\t\t\t\t\t");
                        }
                        cnt++;
                    }
                    fprintf(DotFl,"\n");
                    fprintf(DotFl,"\t\t\t\t\t\t</TR>\n");

                }

            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
}

void blockBitMapDot(FILE* DotFl,int iN){
    char* tS = newString(20);
    
    fprintf(DotFl,"\t\tBlockBitMap\n");
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#66ffb3\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#00cc66",":: BlockBitMap ::",20);

                int extra = ((iN * 3) % 20);
                int nRow  =  (iN * 3) - extra;

                int cnt = 0;
                char ch;
                while(cnt < nRow){

                    if( (cnt + 20) % 20 == 0 ){
                        fprintf(DotFl,"\t\t\t\t\t\t<TR>\n");
                        fprintf(DotFl,"\t\t\t\t\t\t\t");
                    }

                    ch = BinRead_SingleChar(Omni->SBinuse->s_bm_block_start + cnt);
                    fprintf(DotFl,"<TD>%c</TD>",ch);

                    if( (cnt + 1) >= 5 && (cnt + 1) % 5 == 0 ){
                        fprintf(DotFl,"\n");
                        fprintf(DotFl,"\t\t\t\t\t\t\t");
                    }

                    if( (cnt + 1) >= 20 && (cnt + 1) % 20 == 0 ){
                        fprintf(DotFl,"</TR>\n");
                    }
                    cnt++;
                }

                if(extra > 0){
                    fprintf(DotFl,"\t\t\t\t\t\t<TR>\n");
                    fprintf(DotFl,"\t\t\t\t\t\t\t");

                    while(cnt < (iN * 3)){
                        ch = BinRead_SingleChar(Omni->SBinuse->s_bm_block_start + cnt);
                        fprintf(DotFl,"<TD>%c</TD>",ch);
                        if( (cnt + 1) >= 5 && (cnt + 1) % 5 == 0 ){
                            fprintf(DotFl,"\n");
                            fprintf(DotFl,"\t\t\t\t\t\t\t");
                        }
                        cnt++;
                    }
                    fprintf(DotFl,"\n");
                    fprintf(DotFl,"\t\t\t\t\t\t</TR>\n");
                }

            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
}

void AddInode(FILE* DotFl,int ID){

    //int ID = StartByte_to_InodeBit(StartByte);

    char* tS = newString(20);

    Inode* Tinp = (Inode*)BinLoad_Str(ID,"Inode");

    sprintf(tS, "%d",ID);

    fprintf(DotFl,"\t\tInode_%s\n",tS);
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#99c2ff\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#0066ff",Concat_Izq_with_Der(newString("Inode: "),tS,'s','s'),2);

                sprintf(tS, "%d",Tinp->i_uid);
                AddRow(DotFl,"i_uid",tS);

                sprintf(tS, "%d",Tinp->i_gid);
                AddRow(DotFl,"i_gid",tS);

                sprintf(tS, "%d",Tinp->i_size);
                AddRow(DotFl,"i_size",tS);

                sprintf(tS, "%d",Tinp->i_atime);
                AddRow(DotFl,"i_atime",tS);

                sprintf(tS, "%d",Tinp->i_ctime);
                AddRow(DotFl,"i_ctime",tS);

                sprintf(tS, "%d",Tinp->i_mtime);
                AddRow(DotFl,"i_mtime",tS);

                sprintf(tS, "%d",Tinp->i_type);
                AddRow(DotFl,"i_type",tS);

                sprintf(tS, "%d",Tinp->i_perm);
                AddRow(DotFl,"i_perm",tS);

                int cnt = 0;
                while(cnt < 12){

                    if(Tinp->i_block[cnt] == -1){
                        cnt++;
                        continue;
                    }
                    sprintf(tS, "%d",Tinp->i_block[cnt]);

                    char Tp[5];
                    sprintf(Tp, "%d",cnt);

                    char* Ident = Concat_Izq_with_Der(newString("direct_"),Tp,'s','s');

                    AddRow(DotFl,Ident,tS);
                    cnt++;
                }

                if(Tinp->i_block[12] >= 0){
                    sprintf(tS, "%d",Tinp->i_block[12]);
                    AddRow(DotFl,"indirect_12",tS);
                }

                if(Tinp->i_block[13] >= 0){
                    sprintf(tS, "%d",Tinp->i_block[13]);
                    AddRow(DotFl,"indirect_13",tS);
                }

                if(Tinp->i_block[14] >= 0){
                    sprintf(tS, "%d",Tinp->i_block[14]);
                    AddRow(DotFl,"indirect_14",tS);
                }

                fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
}

void AddFileBlock(FILE* DotFl,int ID){

    //int ID = StartByte_to_BlockBit(StartByte);

    char* tS = newString(20);

    FileBlock* Tmp = (FileBlock*)BinLoad_Str(ID,"FileBlock");

    sprintf(tS, "%d",ID);

    fprintf(DotFl,"\t\tFileBlock_%s\n",tS);

    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#ffe066\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#ffcc00",Concat_Izq_with_Der(newString("FileBlock: "),tS,'s','s'),2);
                
                AddRow(DotFl,"b_content",&Tmp->b_content[0]);

            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
}

void AddFolderBlock(FILE* DotFl,int ID){

    //int ID = StartByte_to_BlockBit(StartByte);
    char* tS = newString(20);

    FolderBlock* Tmp = (FolderBlock*)BinLoad_Str(ID,"FolderBlock");

    sprintf(tS, "%d",ID);

    fprintf(DotFl,"\t\tFolderBlock_%s\n",tS);
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#ffb380\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#ff660",Concat_Izq_with_Der(newString("FolderBlock: "),tS,'s','s'),2);

                AddTwinRow(DotFl,Tmp->b_content[0].b_name,toString(&Tmp->b_content[0].b_inodo,'i'),"#ffcc66");
                AddTwinRow(DotFl,Tmp->b_content[1].b_name,toString(&Tmp->b_content[1].b_inodo,'i'),"#ffffff");
                AddTwinRow(DotFl,Tmp->b_content[2].b_name,toString(&Tmp->b_content[2].b_inodo,'i'),"#ffcc66");
                AddTwinRow(DotFl,Tmp->b_content[3].b_name,toString(&Tmp->b_content[3].b_inodo,'i'),"#ffffff");
                /*
                AddRow(DotFl,"name_0",Tmp->b_content[0].b_name);
                sprintf(tS, "%d",Tmp->b_content[0].b_inodo);
                AddRow(DotFl,"inodePtr_0",tS);

                AddRow(DotFl,"name_1",Tmp->b_content[1].b_name);
                sprintf(tS, "%d",Tmp->b_content[1].b_inodo);
                AddRow(DotFl,"inodePtr_1",tS);

                AddRow(DotFl,"name_2",Tmp->b_content[2].b_name);
                sprintf(tS, "%d",Tmp->b_content[2].b_inodo);
                AddRow(DotFl,"inodePtr_2",tS);

                AddRow(DotFl,"name_3",Tmp->b_content[3].b_name);
                sprintf(tS, "%d",Tmp->b_content[3].b_inodo);
                AddRow(DotFl,"inodePtr_3",tS);
                */
 
                
            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
    
}

void AddPointerBlock(FILE* DotFl,int ID){
    //int ID = StartByte_to_BlockBit(StartByte);
    char* tS = newString(20);

    PointerBlock* Tmp = (PointerBlock*)BinLoad_Str(ID,"PointerBlock");

    sprintf(tS, "%d",ID);

    fprintf(DotFl,"\t\tPointerBlock_%s\n",tS);
    fprintf(DotFl,"\t\t\t[label =\n");
        fprintf(DotFl,"\t\t\t\t<\n");
            fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#80ff80\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
                AddSuper(DotFl,"#00cc00",Concat_Izq_with_Der(newString("PointerBlock: "),tS,'s','s'),2);

                int cnt = 0;
                while(cnt < 16){
                    sprintf(tS, "%d",Tmp->b_pointers[cnt]);

                    char Tp[5];
                    sprintf(Tp, "%d",cnt);

                    char* Ident = Concat_Izq_with_Der(newString("pointer_"),Tp,'s','s');

                    AddRow(DotFl,Ident,tS);
                    cnt++;
                }

    
            fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
        fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t];\n");

}

void AddLink(FILE* DotFl,char* Izq,char* Der){
    fprintf(DotFl,"\t\t%s->%s;\n",Izq,Der);
}

char* getGraphStructName(char* Type,int ID){
    char* tS = newString(20);
    sprintf(tS, "%s_%d",Type,ID);
    return tS;
}

void FileSystemTree(FILE* DotFl,char* FatherName,int iNode_Bit_ID,char* Type,char* Qt){
    if(strcasecmp(Type,"Inode") == 0){

        //Son Link Name
        char* SonName = getGraphStructName("Inode",iNode_Bit_ID);

        //Linking
        if(FatherName != NULL){
            AddLink(DotFl,FatherName,SonName);
        }
        
        AddInode(DotFl,iNode_Bit_ID);

        Inode* Rt = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");

        int cnt = 0;
        while(cnt < 15){
            if(Rt->i_block[cnt] == -1){cnt++; continue;}

            int Grandson_ID_Bit = Rt->i_block[cnt];

            if(cnt >= 12){  

                //Folder
                if(Rt->i_type == 0){
                    FileSystemTree(DotFl,SonName,Grandson_ID_Bit,"PointerBlock","Folder");
                }

                //File
                if(Rt->i_type == 1){
                    FileSystemTree(DotFl,SonName,Grandson_ID_Bit,"PointerBlock","File");
                }
                
                cnt++; 
                continue;
            }

            //Folder
            if(Rt->i_type == 0){
                FileSystemTree(DotFl,SonName,Grandson_ID_Bit,"FolderBlock",NULL);
            }

            //File
            if(Rt->i_type == 1){
                FileSystemTree(DotFl,SonName,Grandson_ID_Bit,"FileBlock",NULL);
            }
            cnt++;
        }
    }

    if(strcasecmp(Type,"FileBlock") == 0){
        //Son Link Name
        char* SonName = getGraphStructName("FileBlock",iNode_Bit_ID);

        //Linking
        AddLink(DotFl,FatherName,SonName);

        AddFileBlock(DotFl,iNode_Bit_ID);
    }

    if(strcasecmp(Type,"FolderBlock") == 0){
        AddFolderBlock(DotFl,iNode_Bit_ID);

        //Son Link Name
        char* SonName = getGraphStructName("FolderBlock",iNode_Bit_ID);

        //Linking
        AddLink(DotFl,FatherName,SonName);

        //******* FolderBlock Tour ******
        FolderBlock* Fb = (FolderBlock*)BinLoad_Str(iNode_Bit_ID,"FolderBlock");
        int i = 0;
        while(i < 4){
            if(Fb->b_content[i].b_inodo == -1){i++; continue;}

            char* iName  = newString(Fb->b_content[i].b_name);
            int Next_ID_Bit = Fb->b_content[i].b_inodo; 
            char* NextName = getGraphStructName("Inode",Next_ID_Bit);

            if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){
                FileSystemTree(DotFl,SonName,Next_ID_Bit,"Inode",NULL);
            }
            i++;
        }
    }

    if(strcasecmp(Type,"PointerBlock") == 0){

        AddPointerBlock(DotFl,iNode_Bit_ID);

        //Son Link Name
        char* SonName = getGraphStructName("PointerBlock",iNode_Bit_ID);

        //Linking
        AddLink(DotFl,FatherName,SonName);

        //******* PointerBlock Tour ******
        PointerBlock* Pb = (PointerBlock*)BinLoad_Str(iNode_Bit_ID,"PointerBlock");
        int z = 0;
        while(z < 16){
            if(Pb->b_pointers[z] == -1){z++; continue;}

            int Next_ID_Bit = Pb->b_pointers[z];

            //Folder
            if(strcasecmp(Qt,"Folder") == 0){
                FileSystemTree(DotFl,SonName,Next_ID_Bit,"FolderBlock",NULL);
            }

            //File
            if(strcasecmp(Qt,"File") == 0){
                FileSystemTree(DotFl,SonName,Next_ID_Bit,"FileBlock",NULL);
            }
            z++;
        }
    }
}


/*
void FileSystemTree(FILE* DotFl,int iNode_Bit_ID){

    //Type 0 ---> Folder
    //Type 1 ---> File

    Inode* Rt = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");
    AddInode(DotFl,iNode_Bit_ID);

    //Father Link Name
    char* FatherName = getGraphStructName("Inode",iNode_Bit_ID);

    int cnt = 0;
    
    //Direct
    while(cnt < 12){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];

        //Folder
        if(Rt->i_type == 0){
            AddFolderBlock(DotFl,Son_ID_Bit);

            //Son Link Name
            char* SonName = getGraphStructName("FolderBlock",Son_ID_Bit);

            //Linking
            AddLink(DotFl,FatherName,SonName);

            //******* FolderBlock Tour ******
            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Son_ID_Bit,"FolderBlock");
            int i = 0;
            while(i < 4){
                if(Fb->b_content[i].b_inodo == -1){i++; continue;}

                char* iName  = newString(Fb->b_content[i].b_name);
                int Next_ID_Bit = Fb->b_content[i].b_inodo; 
                char* NextName = getGraphStructName("Inode",Next_ID_Bit);

                if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){

                    //Next Linking
                    AddLink(DotFl,SonName,NextName);
                    FileSystemTree(DotFl,Next_ID_Bit);
                }
                i++;
            }
        }

        //File
        if(Rt->i_type == 1){
            AddFileBlock(DotFl,Son_ID_Bit);

            //Son Link Name
            char* SonName = getGraphStructName("FileBlock",Son_ID_Bit);

            //Linking
            AddLink(DotFl,FatherName,SonName);
        }
        cnt++;
    }

    //Indirect
    while(cnt < 15){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];
        AddPointerBlock(DotFl,Son_ID_Bit);

        //Son Link Name
        char* SonName = getGraphStructName("PointerBlock",Son_ID_Bit);

        //Linking
        AddLink(DotFl,FatherName,SonName);
        
        //******* PointerBlock Tour ******
        PointerBlock* Pb = (PointerBlock*)BinLoad_Str(Son_ID_Bit,"PointerBlock");
        int z = 0;
        while(z < 16){
            if(Pb->b_pointers[z] == -1){z++; continue;}

            int Next_ID_Bit = Pb->b_pointers[z];

            char* NextName;
            

            //Folder
            if(Rt->i_type == 0){
                AddFolderBlock(DotFl,Next_ID_Bit);
                NextName = getGraphStructName("FolderBlock",Next_ID_Bit);


                //******* FolderBlock Tour ******
                FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Next_ID_Bit,"FolderBlock");
                int i = 0;
                while(i < 4){
                    char* iName  = newString(Fb->b_content[i].b_name);
                    int SuperNext_ID_Bit = Fb->b_content[i].b_inodo; 
                    char* SuperNextName = getGraphStructName("Inode",SuperNext_ID_Bit);

                    if(SuperNext_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){
                        //Next Linking
                        AddLink(DotFl,NextName,SuperNextName);
                        FileSystemTree(DotFl,SuperNext_ID_Bit);
                    }
                    i++;
                }
            }

            //File
            if(Rt->i_type == 1){
                AddFileBlock(DotFl,Next_ID_Bit);
                NextName = getGraphStructName("FileBlock",Next_ID_Bit);
            }

            //Linking
            AddLink(DotFl,SonName,NextName);

            z++;
        }

        cnt++;
    }    
}
*/


void InodeOnlyDot(FILE* DotFl,int iN){

    int Base = Omni->SBinuse->s_bm_inode_start;
    int cnt = 0;
    char* lsName = NULL;
    while(cnt < iN){
        //int Bit_ID = cnt;
        int StartByte = Bit_to_StartByte(cnt,"Inode");
        char chBit    = BinRead_SingleChar(Omni->SBinuse->s_bm_inode_start + cnt);
        Inode* tmp = (Inode*)BinLoad_Str(cnt,"Inode");
        if(chBit == '1'){
            Inode* tmp = (Inode*)BinLoad_Str(cnt,"Inode");
            AddInode(DotFl,cnt);
            char* Izq_Name = getGraphStructName("Inode",cnt);
            if(lsName != NULL && (cnt + 1 != iN)){
                AddLink(DotFl,lsName,Izq_Name);
            }
            lsName = Izq_Name;
        }
        cnt++;
    }
    
}

int CheckRank(int N){
    if(N > -2 && N < 1500){
        return 1;
    }
    return 0;
}

int isFolderBlock(int Bit_ID){
    FolderBlock* Folder = (FolderBlock*)BinLoad_Str(Bit_ID,"FolderBlock");

    int cnt = 0;
    while(cnt < 4){
        int tmp = Folder->b_content[cnt].b_inodo;
        if(CheckRank(tmp) == 0){
            return 0;
        }
        cnt++;
    }

    return 1;
}

int isPointerBlock(int Bit_ID){
    PointerBlock* Pointer = (PointerBlock*)BinLoad_Str(Bit_ID,"PointerBlock");

    int cnt = 0;
    while(cnt < 16){
        int tmp = Pointer->b_pointers[cnt];
        if(CheckRank(tmp) == 0){
            return 0;
        }
        cnt++;
    }
    return 1;
}

void BlockOnlyDot(FILE* DotFl,int iN){

    int Base = Omni->SBinuse->s_bm_block_start;
    int cnt = 0;
    char* lsName = NULL;
    while(cnt < (iN * 3)){
        //int Bit_ID = cnt;
        int StartByte = Bit_to_StartByte(cnt,"Block");
        char chBit    = BinRead_SingleChar(Omni->SBinuse->s_bm_block_start + cnt);

        if(chBit == '1'){

            if(cnt == 73){
                int asdf = 584;
            }

            
            if(isPointerBlock(cnt) == 1){

                PointerBlock* tmp = (PointerBlock*)BinLoad_Str(cnt,"PointerBlock");
                AddPointerBlock(DotFl,cnt);
                char* Izq_Name = getGraphStructName("PointerBlock",cnt);
                if(lsName != NULL && (cnt + 1 != iN)){
                    AddLink(DotFl,lsName,Izq_Name);
                }
                lsName = Izq_Name;
            }
            else if(isFolderBlock(cnt) == 1){

                FolderBlock* tmp = (FolderBlock*)BinLoad_Str(cnt,"FolderBlock");
                AddFolderBlock(DotFl,cnt);
                char* Izq_Name = getGraphStructName("FolderBlock",cnt);
                if(lsName != NULL && (cnt + 1 != iN)){
                    AddLink(DotFl,lsName,Izq_Name);
                }
                lsName = Izq_Name;

            }
            else{

                FileBlock* tmp = (FileBlock*)BinLoad_Str(cnt,"FileBlock");
                AddFileBlock(DotFl,cnt);
                char* Izq_Name = getGraphStructName("FileBlock",cnt);
                if(lsName != NULL && (cnt + 1 != iN)){
                    AddLink(DotFl,lsName,Izq_Name);
                }
                lsName = Izq_Name;

            }
        }
        cnt++;
    }
}

//(^< ............ ............ ...........   txt_InodeBitMap
void txt_InodeBitMap(char* CompleteReportPathDir,char* VD){

    char* tim = newString("/*** -> InodeBitMap: ");
    tim = Concat_Izq_with_Der(tim,VD,'s','s');
    tim = Concat_Izq_with_Der(tim,newString(" <- ***/\n\n"),'s','s');


    int iN = Calc_iN(Omni->PartBatch_inUse->Size);

    /*
    int iN = -1;
    if(Usr_inUse->SBinuse->s_filesystem_type == 3){
        iN = Usr_inUse->Ext3_iN;
    }
    else{
        iN = Usr_inUse->Ext2_iN;
    }
    */

    int Base = Omni->SBinuse->s_bm_inode_start;
    int cnt = 0;
    int Fp  = 0;
   
    char txtContent[900000];
    memset(txtContent,'\0',900000);
    strcpy(txtContent,tim);
    
    
    while(cnt < iN){

        char chBit = BinRead_SingleChar(Omni->SBinuse->s_bm_inode_start + cnt);
        
        if(cnt != 0 && ((cnt + 1) % 20) == 0){
            txtContent[Fp] = chBit;
            Fp++;
            
            txtContent[Fp] = '\n';
            Fp++;
        }
        else{
        
            txtContent[Fp] = chBit;
            Fp++;

            txtContent[Fp] = ' ';
            Fp++;

            txtContent[Fp] = ' ';
            Fp++;
        
        }
        cnt++;
    }

    char* pps = Concat_Izq_with_Der(tim,txtContent,'s','s');
    strcpy(txtContent,pps);

    //char* Ext_ReportName = Path_Get_FileName(CompleteReportPathDir);
    char* Ext_ReportPath = Path_Get_Isolated(CompleteReportPathDir);

    CreatePathDir(Ext_ReportPath);
    Write_txtFile(CompleteReportPathDir,txtContent);
    
}

//(^< ............ ............ ...........   txt_BlockBitMap
void txt_BlockBitMap(char* CompleteReportPathDir,char* VD){

    char* tim = newString("/*** -> BlockBitMap: ");
    tim = Concat_Izq_with_Der(tim,VD,'s','s');
    tim = Concat_Izq_with_Der(tim,newString(" <- ***/\n\n"),'s','s');

    int iN = Calc_iN(Omni->PartBatch_inUse->Size);

    int Base = Omni->SBinuse->s_bm_block_start;
    int cnt = 0;
    int Fp  = 0;

    char txtContent[900000];
    memset(txtContent,'\0',900000);
    
    while(cnt < (3 * iN)){

        char chBit = BinRead_SingleChar(Omni->SBinuse->s_bm_block_start + cnt);
        
        if(cnt != 0 && ((cnt + 1) % 20) == 0){
            txtContent[Fp] = chBit;
            Fp++;
            
            txtContent[Fp] = '\n';
            Fp++;
        }
        else{
        
            txtContent[Fp] = chBit;
            Fp++;

            txtContent[Fp] = ' ';
            Fp++;

            txtContent[Fp] = ' ';
            Fp++;
        
        }
        cnt++;
    }

    char* pps = Concat_Izq_with_Der(tim,txtContent,'s','s');
    strcpy(txtContent,pps);

    char* Ext_ReportName = Path_Get_FileName(CompleteReportPathDir);
    char* Ext_ReportPath = Path_Get_Isolated(CompleteReportPathDir);

    CreatePathDir(Ext_ReportPath);
    Write_txtFile(CompleteReportPathDir,txtContent);
}

char* int_to_OctalPerm(char tS){
    char* Sp = newString(3);

    if(tS == '0'){
        Sp = newString("---");
    }
    else if(tS == '1'){
        Sp = newString("--x");
    }
    else if(tS == '2'){
        Sp = newString("-w-");
    }
    else if(tS == '3'){
        Sp = newString("-wx");
    }
    else if(tS == '4'){
        Sp = newString("r--");
    }
    else if(tS == '5'){
        Sp = newString("r-x");
    }
    else if(tS == '6'){
        Sp = newString("rw-");
    }
    else if(tS == '7'){
        Sp = newString("rwx");
    }

    return Sp;
}

char* getPermitString(int Perm){
    char* tS = newString(3);
    sprintf(tS,"%d",Perm);

    char* _1 = int_to_OctalPerm(tS[0]);
    char* _2 = int_to_OctalPerm(tS[1]);
    char* _3 = int_to_OctalPerm(tS[2]);

    char* Cmp = Concat_Izq_with_Der(_1,newString(" "),'s','s');
    Cmp = Concat_Izq_with_Der(Cmp,_2,'s','s');
    Cmp = Concat_Izq_with_Der(Cmp,newString(" "),'s','s');
    Cmp = Concat_Izq_with_Der(Cmp,_3,'s','s');

    return Cmp;
}

void Add_LsRow(FILE* DotFl,int Bit_ID,char* Type,char* Name){

    Inode* tmp = (Inode*)BinLoad_Str(Bit_ID,"Inode");
    char* Permision = getPermitString(tmp->i_perm);
    GroupUserInfo* Usr = getUSR_by_ID(tmp->i_uid);
    GroupUserInfo* Grp = getGRP_by_ID(tmp->i_gid);
    char* Owner = newString(Usr->UsrName);
    char* Group = newString(Usr->GrpName);

    char* Size_in_Bytes = newString(25);
    sprintf(Size_in_Bytes,"%d",tmp->i_size);

    char* Date = newString(25);
    sprintf(Date,"%d",tmp->i_mtime);
    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD>%s</TD><TD>%i</TD><TD>%s</TD><TD>%s</TD><TD>%s</TD><TD>%s</TD><TD>%s</TD><TD>%s</TD></TR>\n",Permision,tmp->i_perm,Owner,Group,Size_in_Bytes,Date,Type,Name);
}

void Add_Father(FILE* DotFl,int Bit_ID,char* Type,char* Name){

    Inode* tmp = (Inode*)BinLoad_Str(Bit_ID,"Inode");
    char* Permision = getPermitString(tmp->i_perm);
    GroupUserInfo* Usr = getUSR_by_ID(tmp->i_uid);
    GroupUserInfo* Grp = getGRP_by_ID(tmp->i_gid);
    char* Owner = newString(Usr->UsrName);
    char* Group = newString(Usr->GrpName);

    char* Size_in_Bytes = newString(25);
    sprintf(Size_in_Bytes,"%d",tmp->i_size);

    char* Date = newString(25);
    sprintf(Date,"%d",tmp->i_mtime);
    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%i</TD><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%s</TD><TD bgcolor= \"#cc66ff\">%s</TD></TR>\n",Permision,tmp->i_perm,Owner,Group,Size_in_Bytes,Date,Type,Name);
}

void LsTravel(FILE* DotFl,int iNode_Bit_ID){

    /*
    //Type 0 ---> Folder
    //Type 1 ---> File

    Inode* Rt = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");
    //AddInode(DotFl,iNode_Bit_ID);

    //Father Link Name
    //char* FatherName = getGraphStructName("Inode",iNode_Bit_ID);

    int cnt = 0;
    
    //Direct
    while(cnt < 12){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];

        //Folder
        if(Rt->i_type == 0){
            //Son Link Name
            char* SonName = getGraphStructName("FolderBlock",Son_ID_Bit);
            //******* FolderBlock Tour ******
            FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Son_ID_Bit,"FolderBlock");
            int i = 0;
            while(i < 4){
                if(Fb->b_content[i].b_inodo == -1){i++; continue;}

                char* iName  = newString(Fb->b_content[i].b_name);
                int Next_ID_Bit = Fb->b_content[i].b_inodo; 


                if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){
                    Inode* next_i_Node = (Inode*)BinLoad_Str(Next_ID_Bit,"Inode");
                    if(next_i_Node->i_type == 0){
                        //Folder
                        Add_LsRow(DotFl,Next_ID_Bit,"Folder",iName);
                        //LsTravel(DotFl,next_i_Node_Bit_ID);
                    }
                    else{
                        Add_LsRow(DotFl,Next_ID_Bit,"Archivo",iName);
                    }
                }
                i++;
            }
        }

        //File
        if(Rt->i_type == 1){

        }
        cnt++;
    }

    //Indirect
    while(cnt < 15){
        if(Rt->i_block[cnt] == -1){cnt++; continue;}

        int Son_ID_Bit = Rt->i_block[cnt];
        
        //******* PointerBlock Tour ******
        PointerBlock* Pb = (PointerBlock*)BinLoad_Str(Son_ID_Bit,"PointerBlock");
        int z = 0;
        while(z < 16){
            if(Pb->b_pointers[z] == -1){z++; continue;}

            int Next_ID_Bit = Pb->b_pointers[z];
            char* NextName;
            
            //Folder
            if(Rt->i_type == 0){

                //******* FolderBlock Tour ******
                FolderBlock* Fb = (FolderBlock*)BinLoad_Str(Son_ID_Bit,"FolderBlock");
                int i = 0;
                while(i < 4){
                    if(Fb->b_content[i].b_inodo == -1){i++; continue;}

                    char* iName  = newString(Fb->b_content[i].b_name);
                    int Next_ID_Bit = Fb->b_content[i].b_inodo; 

                    if(Next_ID_Bit > -1 && strcasecmp(iName,"iNodeFather") != 0 && strcasecmp(iName,"iNodeCurent") != 0){
                        Inode* next_i_Node = (Inode*)BinLoad_Str(Next_ID_Bit,"Inode");
                        if(next_i_Node->i_type == 0){
                            //Folder
                            Add_LsRow(DotFl,Next_ID_Bit,"Folder",iName);
                            //LsTravel(DotFl,next_i_Node_Bit_ID);
                        }
                        else{
                            Add_LsRow(DotFl,Next_ID_Bit,"Archivo",iName);
                        }
                    }
                    i++;
                }
            }

            //File
            if(Rt->i_type == 1){

            }
            z++;
        }

        cnt++;
    }

    */    


    Inode* i_Node = (Inode*)BinLoad_Str(iNode_Bit_ID,"Inode");
    int i = 0;
    while (i < 12){

        if(i_Node->i_block[i] == -1) {i++; continue;}

        int FB_Bit_ID = i_Node->i_block[i];
        FolderBlock* FolderB = (FolderBlock*)BinLoad_Str(FB_Bit_ID,"FolderBlock");

        int j = 0;
        //int Empty = 0;
        while (j < 4){
            //Carpeta no Vacia solo con Empty carpeta4
            if(FolderB->b_content[j].b_inodo == -1) {j++; continue;}

            int next_i_Node_Bit_ID = FolderB->b_content[j].b_inodo;
            char* tName = FolderB->b_content[j].b_name;
            Inode* next_i_Node = (Inode*)BinLoad_Str(next_i_Node_Bit_ID,"Inode");

            int isFolder  = !next_i_Node->i_type; 
            int isCurrent = strcasecmp(FolderB->b_content[j].b_name,"iNodeFather");
            int isFather  = strcasecmp(FolderB->b_content[j].b_name,"iNodeCurent");
            
            if(isFolder && isCurrent != 0 && isFather != 0){
                //Folder
                Add_LsRow(DotFl,next_i_Node_Bit_ID,"Folder",tName);
            }
            else{
                //File
                if(isFolder == 0){
                    Add_LsRow(DotFl,next_i_Node_Bit_ID,"Archivo",tName);
                }
            }
            j++;
        }

        i++;
    }

    while (i < 15){
        if(i_Node->i_block[i] == -1) {i++; continue;}
         int Son_ID_Bit = i_Node->i_block[i];
        
        //******* PointerBlock Tour ******
        PointerBlock* Pb = (PointerBlock*)BinLoad_Str(Son_ID_Bit,"PointerBlock");
        int z = 0;
        while(z < 16){
            if(Pb->b_pointers[z] == -1) {z++; continue;}
            int FB_Bit_ID = Pb->b_pointers[z];
            FolderBlock* FolderB = (FolderBlock*)BinLoad_Str(FB_Bit_ID,"FolderBlock");
            
            int j = 0;
            //int Empty = 0;
            while (j < 4){
                //Carpeta no Vacia solo con Empty carpeta4
                if(FolderB->b_content[j].b_inodo == -1) {j++; continue;}

                int next_i_Node_Bit_ID = FolderB->b_content[j].b_inodo;
                char* tName = FolderB->b_content[j].b_name;
                Inode* next_i_Node = (Inode*)BinLoad_Str(next_i_Node_Bit_ID,"Inode");

                int isFolder  = !next_i_Node->i_type; 
                int isCurrent = strcasecmp(FolderB->b_content[j].b_name,"iNodeFather");
                int isFather  = strcasecmp(FolderB->b_content[j].b_name,"iNodeCurent");
                
                if(isFolder && isCurrent != 0 && isFather != 0){
                    //Folder
                    Add_LsRow(DotFl,next_i_Node_Bit_ID,"Folder",tName);
                }
                else{
                    //File
                    if(isFolder == 0){
                        Add_LsRow(DotFl,next_i_Node_Bit_ID,"Archivo",tName);
                    }
                }
                j++;
            }
            z++;
        }
        i++;
    }
}

void Generate_Ls_Rep(char* CompleteReportPathDir,char* _ruta){

    char* Name = newString("hola");
    if(strcasecmp(_ruta,"/") != 0){
        DoublyGenericList* Ph = PathSeparate(_ruta);
        Pop(Ph);
        Name = (char*)Pop(Ph);
    }

    char* DotPath = get_DotExt_Path(CompleteReportPathDir);
    int iN = Calc_iN(Omni->PartBatch_inUse->Size);

    //(^< ............ ............ ............   R E P O R T
    
    char* ReportName = Path_Get_FileName(CompleteReportPathDir);
    char* ReportPath = Path_Get_Isolated(CompleteReportPathDir);

    CreatePathDir(ReportPath);
    
    FILE* DotFl = fopen(DotPath,"w+");

    //(^< ............ ............ ...........   D O T   F I L E
    if(DotFl){
        fprintf(DotFl,"digraph FullView {\n");
        fprintf(DotFl,"\trankdir = LR;\n");
        fprintf(DotFl,"\tnode [shape = plaintext];\n");
        fprintf(DotFl,"\t\tsubgraph cluster_OutLook {\n");
        fprintf(DotFl,"\t\t\tlabel = \"LS Report :: %s\";\n",_ruta);
        fprintf(DotFl,"\t\t\tgraph[style = dotted];\n");

        //(^< ............ ............ ...........   Ls
        fprintf(DotFl,"\t\tLs_Report\n");
        fprintf(DotFl,"\t\t\t[label =\n");
            fprintf(DotFl,"\t\t\t\t<\n");
                fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#99c2ff\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");

                
                //SeekInfo* nsk = newSeekInfo();
                //InfoCatcher* nwInf = newInfoCatcher();
                int iNode_Bit_ID;
                Existence* ex = vFF_Exists(_ruta);
                if(strcasecmp(_ruta,"/") != 0){
                    //nwInf->_ruta = _ruta;
                    iNode_Bit_ID = ex->iNode;
                }
                else{
                    iNode_Bit_ID = 0;
                }

                if(Check_If_Is_txtFile(ex->FFName)){
                    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor= \"#cc66ff\">Permission String</TD><TD bgcolor= \"#cc66ff\">Permission Int</TD><TD bgcolor= \"#cc66ff\">Owner</TD><TD bgcolor= \"#cc66ff\">Group</TD><TD bgcolor= \"#cc66ff\">Size_in_Bytes</TD><TD bgcolor= \"#cc66ff\">Date</TD><TD bgcolor= \"#cc66ff\">Type</TD><TD bgcolor= \"#cc66ff\">Name</TD></TR>\n");
                    Add_Father(DotFl,ex->iNode,"Archivo",ex->FFName);
                }
                else{
                    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor= \"#cc66ff\">Permission String</TD><TD bgcolor= \"#cc66ff\">Permission Int</TD><TD bgcolor= \"#cc66ff\">Owner</TD><TD bgcolor= \"#cc66ff\">Group</TD><TD bgcolor= \"#cc66ff\">Size_in_Bytes</TD><TD bgcolor= \"#cc66ff\">Date</TD><TD bgcolor= \"#cc66ff\">Type</TD><TD bgcolor= \"#cc66ff\">Name</TD></TR>\n");
                    Add_Father(DotFl,iNode_Bit_ID,"Folder",ex->FFName);
                    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor= \"#ffffff\" colspan=\"8\">- -</TD></TR>\n");
                    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD>Permission String</TD><TD>Permission Int</TD><TD>Owner</TD><TD>Group</TD><TD>Size_in_Bytes</TD><TD>Date</TD><TD>Type</TD><TD>Name</TD></TR>\n");
                    LsTravel(DotFl,iNode_Bit_ID);
                }
                fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
            fprintf(DotFl,"\t\t\t\t>\n");
        fprintf(DotFl,"\t\t\t]\n");

        fprintf(DotFl,"\t\t}\n");
        fprintf(DotFl,"}\n");
        fclose(DotFl);
        //Generate_TypeFile_Rep(CompleteReportPathDir);
    }
}

void Add_Jr_Body(FILE* DotFl){

    int Jr_StartByte = Omni->PartBatch_inUse->StartByte + sizeof(SuperBlock);

    int iN = Omni->SBinuse->s_inodes_count;
    int i = 0;
    
    while(i < iN){
        Journaling* tmp = (Journaling*)BinLoad_Str(Jr_StartByte + (i * sizeof(Journaling)),"Journaling");
        char* CMD   = newString(tmp->CMD);
        char* Param = newString(tmp->Content);
        if(tmp->isOccupied == '0' || tmp->isOccupied != '1'){
            break;
        }
        if(tmp->isOccupied != '0'){
            if(strcasecmp(CMD,"login") != 0 && strcasecmp(CMD,"logout") != 0){

                DoublyGenericList* CommandList = new_DoublyGenericList();
                char* Main_CMD = strtok(Param, " ");
                FillCommandList(Main_CMD,CommandList);
                InfoCatcher* nwInf = newInfoCatcher();
                fillInfoCatcher(CommandList,&nwInf);
                char* Cnt = nwInf->_path;
                if(nwInf->_path == NULL){

                    if(strcasecmp(CMD,"mkgrp") == 0){
                        Cnt = Concat_Izq_with_Der(newString("name = "),nwInf->_name,'s','s');
                    }

                    if(strcasecmp(CMD,"rmgrp") == 0){
                        Cnt = Concat_Izq_with_Der(newString("name = "),nwInf->_name,'s','s');
                    }

                    if(strcasecmp(CMD,"mkusr") == 0){
                        Cnt = Concat_Izq_with_Der(newString("usr = "),nwInf->_usr,'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                        Cnt = Concat_Izq_with_Der(Cnt,newString("pwd = "),'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,nwInf->_pwd,'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                        Cnt = Concat_Izq_with_Der(Cnt,newString("grp = "),'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,nwInf->_grp,'s','s');
                    }

                    if(strcasecmp(CMD,"rmusr") == 0){
                        Cnt = Concat_Izq_with_Der(newString("usr = "),nwInf->_usr,'s','s');
                    }

                    if(strcasecmp(CMD,"chgrp") == 0){
                        Cnt = Concat_Izq_with_Der(newString("usr = "),nwInf->_usr,'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                        
                        Cnt = Concat_Izq_with_Der(Cnt,newString("grp = "),'s','s');
                        Cnt = Concat_Izq_with_Der(Cnt,nwInf->_grp,'s','s');
                    }
                }

                if(strcasecmp(CMD,"rem") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                }

                if(strcasecmp(CMD,"mkdir") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("p = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_P,'s','i');
                }

                if(strcasecmp(CMD,"ren") == 0){
                    Cnt = newString("path = ");
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("name = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_name,'s','s');
                }

                if(strcasecmp(CMD,"edit") == 0){
                    Cnt = newString("path = ");
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("cont = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_cont,'s','s');
                }

                if(strcasecmp(CMD,"mkfile") == 0){

                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("p = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_P,'s','i');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("size = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_size,'s','i');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("cont = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_cont,'s','s');
                }

                if(strcasecmp(CMD,"mv") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("dest = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_dest,'s','s');
                }

                if(strcasecmp(CMD,"chmod") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                    
                    Cnt = Concat_Izq_with_Der(Cnt,newString("ugo = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_ugo,'s','i');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("r = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_R,'s','i');
                }

                if(strcasecmp(CMD,"chown") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                    
                    Cnt = Concat_Izq_with_Der(Cnt,newString("usr = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,nwInf->_usr,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');

                    Cnt = Concat_Izq_with_Der(Cnt,newString("r = "),'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,&nwInf->_R,'s','i');
                }

                if(strcasecmp(CMD,"rem") == 0){
                    Cnt = Concat_Izq_with_Der(newString("path = "),nwInf->_path,'s','s');
                    Cnt = Concat_Izq_with_Der(Cnt,newString("<br/>\n"),'s','s');
                }

                char* cls = newString("\"#33ff33\"");
                if(JourColor % 2 == 0){
                    cls = newString("\"#00ace6\"");
                    JourColor++;
                }
                else{
                    cls = newString("\"#33ff33\"");
                    JourColor++;
                }

                char* tps = newString("Archivo");
                if(tmp->isFile_or_Folder == '0'){
                    tps = newString("Folder");
                }
                
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s colspan=\"2\">-                                                           -</TD></TR>\n",cls);
                //fprintf(DotFl,"\t\t\t\t\t\t<TR><TD>En Uso</TD><TD bgcolor=\"#ffffff\">%c</TD></TR>\n",tmp->isOccupied);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Operacion</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,tmp->CMD);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Nombre</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,tmp->File_of_FolderName);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Tipo</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,tps);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Contenido</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,Cnt);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Fecha</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,tmp->Date);
                //fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Propietario</TD><TD bgcolor=\"#ffffff\">%s</TD></TR>\n",cls,tmp->Owner);
                //fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s>Permisos</TD><TD bgcolor=\"#ffffff\">%i</TD></TR>\n",cls,tmp->Permits);
                fprintf(DotFl,"\t\t\t\t\t\t<TR><TD bgcolor=%s colspan=\"2\">-                                                           -</TD></TR>\n",cls);
                //fprintf(DotFl,"\t\t\t\t\t\t<TR><TD> holas <br/> simonx</TD></TR>\n");
                
            }
            
        }
        i++;
    }

}


void Generate_File_Rep(char* CompleteReportPathDir,char* _ruta){

    char* ReportName = Path_Get_FileName(CompleteReportPathDir);
    char* ReportPath = Path_Get_Isolated(CompleteReportPathDir);

    char* iName = Path_Get_FileName(_ruta);

    CreatePathDir(ReportPath);
    char* txtContent = ReadFile(_ruta);
    
    Write_txtFile(CompleteReportPathDir,txtContent);
}


void Generate_Journaling(FILE* DotFl){
    
    fprintf(DotFl,"\t\tLs_Report\n");
    fprintf(DotFl,"\t\t\t[label =\n");
    fprintf(DotFl,"\t\t\t\t<\n");
    fprintf(DotFl,"\t\t\t\t\t<TABLE BGCOLOR = \"#33ff33\" BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\">\n");
    fprintf(DotFl,"\t\t\t\t\t\t<TR><TD>Parametro</TD><TD>Contenido</TD></TR>\n");
    Add_Jr_Body(DotFl);
    fprintf(DotFl,"\t\t\t\t\t</TABLE>\n");
    fprintf(DotFl,"\t\t\t\t>\n");
    fprintf(DotFl,"\t\t\t]\n");
}


void FullViewRender(char* CompleteReportPathDir,char* Type,char* VD){

    //(^< ............ ............ ...........   InodeBitMap
    if(strcasecmp(Type,"bm_inode") == 0){
        txt_InodeBitMap(CompleteReportPathDir,VD);
        //inodeBitMapDot(DotFl,iN);
        return;
    }

    //(^< ............ ............ ...........   BlockBitMap
    if(strcasecmp(Type,"bm_block") == 0){
        txt_BlockBitMap(CompleteReportPathDir,VD);
        //blockBitMapDot(DotFl,iN);
        return;
    }

    char* DotPath = get_DotExt_Path(CompleteReportPathDir);
    int iN = Calc_iN(Omni->PartBatch_inUse->Size);

    //(^< ............ ............ ............   R E P O R T
    
    //char* ReportName = Path_Get_FileName(CompleteReportPathDir);
    char* ReportPath = Path_Get_Isolated(CompleteReportPathDir);

    CreatePathDir(ReportPath);
    
    FILE* DotFl = fopen(DotPath,"w+");

    //(^< ............ ............ ...........   D O T   F I L E
    if(DotFl){
        fprintf(DotFl,"digraph FullView {\n");
        fprintf(DotFl,"\trankdir = LR;\n");
        fprintf(DotFl,"\tnode [shape = plaintext];\n");
        fprintf(DotFl,"\t\tsubgraph cluster_OutLook {\n");
        fprintf(DotFl,"\t\t\tlabel = \"Ext3 :: %s :: %s\";\n",VD,Type);
        fprintf(DotFl,"\t\t\tgraph[style = dotted];\n");

        //(^< ............ ............ ...........   SuperBlock
        if(strcasecmp(Type,"sb") == 0){
            SuperBlockDot(DotFl);
        }
    
        //(^< ............ ............ ...........   Journaling
        if(strcasecmp(Type,"journaling") == 0){
            int jStart = Omni->SBinuse->s_block_start + sizeof(SuperBlock);
            Journaling* Jr = (Journaling*)BinLoad_Str(jStart,"Journaling");
            JourColor = 0;
            Generate_Journaling(DotFl);
        }

        //(^< ............ ............ ...........   FileSystemTree
        if(strcasecmp(Type,"tree") == 0){
            //int StartByte = Bit_to_StartByte(0,"Inode");
            FileSystemTree(DotFl,NULL,0,"Inode",NULL);       
            //FileSystemTree(DotFl,0);       

        }

        //(^< ............ ............ ...........   InodeOnlyDot
        if(strcasecmp(Type,"inode") == 0){
            InodeOnlyDot(DotFl,iN);
        }
        
        //(^< ............ ............ ...........   BlockOnlyDot
        if(strcasecmp(Type,"block") == 0){
            BlockOnlyDot(DotFl,iN);
        }

        fprintf(DotFl,"\t\t}\n");
        fprintf(DotFl,"}\n");
        fclose(DotFl);
        //Generate_TypeFile_Rep(CompleteReportPathDir);
    }
}



#endif // F2_REP