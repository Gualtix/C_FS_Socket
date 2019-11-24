#ifndef F1_REP
#define F1_REP

#include "../Fw/Helper.h"
#include "../Container.h"
#include "../Fw/StringHandler.h"
#include "../Belong.h"

void AddBlock(FILE* DotFl,Batch* GB,char* BlockName,int DiskSize){
    if(GB->Type != 'e'){

        if(GB->Type == 'm'){
            fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#00cc99\" width = \"150\">\n");
        }
        else if(GB->Type == 'p'){
            fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#66ccff\" width = \"150\">\n");
        }
        else if(GB->Type == 's'){
            fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#eff5f5\" width = \"200\">\n");
        }
        else{
            fprintf(DotFl,"\t\t\t\t\t<TD width = \"150\">\n");
        }
    }
    
        fprintf(DotFl,"\t\t\t\t\t\t- %s -<br/>\n",BlockName);
        double PRC = ((double)GB->Size/DiskSize)*100;
        int BlockSize = GB->Size/1024;
        fprintf(DotFl,"\t\t\t\t\t\t %d (Kb)<br/>\n",BlockSize);
        fprintf(DotFl,"\t\t\t\t\t\t%.2f%% del Disco<br/>\n",PRC);
        fprintf(DotFl,"\t\t\t\t\t\tStartByte:%d<br/>\n",GB->StartByte);
        fprintf(DotFl,"\t\t\t\t\t\tEndByte:%d<br/>\n",GB->EndByte);
    
    if(GB->Type != 'e'){
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    }
}

void Add_EBR_Block(FILE* DotFl,Batch* GB,char* BlockName,int DiskSize,int Next){
    if(GB->Type != 'e'){
        fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#ff9900\" width = \"75\">\n");
    }
    
        fprintf(DotFl,"\t\t\t\t\t\t- EBR -<br/>\n");
        fprintf(DotFl,"\t\t\t\t\t\t %s <br/>\n",BlockName);
        fprintf(DotFl,"\t\t\t\t\t\Next:%d<br/>\n",Next);
    
    if(GB->Type != 'e'){
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    }
}

void Add_LogicPart_Block(FILE* DotFl,Batch* GB,char* BlockName,int DiskSize){
    if(GB->Type != 'e'){
        fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#c6ff1a\" width = \"350\">\n");
    }
    
        fprintf(DotFl,"\t\t\t\t\t\t- Logic -<br/>\n");
        fprintf(DotFl,"\t\t\t\t\t\t %s <br/>\n",BlockName);
        double PRC = ((double)GB->Size/DiskSize)*100;
        int BlockSize = GB->Size / 1024;
        fprintf(DotFl,"\t\t\t\t\t\t %d (KBytes)<br/>\n",BlockSize);
        fprintf(DotFl,"\t\t\t\t\t\t%.2f%% del Disco<br/>\n",PRC);
        fprintf(DotFl,"\t\t\t\t\t\tStartByte:%d<br/>\n",GB->StartByte);
        fprintf(DotFl,"\t\t\t\t\t\tEndByte:%d<br/>\n",GB->EndByte);
    
    if(GB->Type != 'e'){
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    }
}

void AddExtended_Block(FILE* DotFl,Batch* GB,char* BlockName,int DiskSize,int ColSpan){
    
    fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#ff5050\" width = \"150\">\n");

        fprintf(DotFl,"\t\t\t\t\t\t<TABLE border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">\n");
        fprintf(DotFl,"\t\t\t\t\t\t\t<TR>\n");
            fprintf(DotFl,"\t\t\t\t\t\t\t\t<TD colspan=\"%d\">\n",100);
            AddBlock(DotFl,GB,BlockName,DiskSize);
            fprintf(DotFl,"\t\t\t\t\t\t\t\t</TD>\n");
        fprintf(DotFl,"\t\t\t\t\t\t\t</TR>\n");

        fprintf(DotFl,"\t\t\t\t\t\t\t<TR>\n");
            while(GB->LgParts->Length > 0){
                Batch* tB = (Batch*)(DeQueue(GB->LgParts));
                
                if(tB->Type == 'q'){
                    //char* Nm = Concat_Izq_with_Der(newString("EBR: "),tB->PartName,'s','s');
                    char* Nm = tB->PartName;
                    
                    Add_EBR_Block(DotFl,tB,Nm,DiskSize,tB->Next);

                    int Cmp = strcasecmp(tB->PartName,"UNDEFINED");
                    if(Cmp != 0){
                        Batch* Lg = newBatch();
                        Lg->StartByte = tB->StartByte;
                        Lg->Size =  tB->Size;
                        Lg->EndByte = tB->EndByte;
                        Lg->Next = tB->Next;
                        Lg->PartName = tB->PartName;
                        Lg->Type = 'l';

                        char* Ps = tB->PartName;
                        Add_LogicPart_Block(DotFl,Lg,Ps,DiskSize);
                    }
                }
                else if(tB->Type == 's'){
                    AddBlock(DotFl,tB,"Space",DiskSize);
                }
                else{
                    char* Nm = Concat_Izq_with_Der(newString("Logic: "),tB->PartName,'s','s');
                    AddBlock(DotFl,tB,Nm,DiskSize);
                }
            }
        fprintf(DotFl,"\t\t\t\t\t\t\t</TR>\n");

    fprintf(DotFl,"\t\t\t\t\t\t</TABLE>\n");
    fprintf(DotFl,"\t\t\t\t\t</TD>\n");
}

void AddBatch(FILE* DotFl,DoublyGenericList* btList,int DiskSize){
    while(btList->Length > 0){
        Batch* Bt = (Batch*)DeQueue(btList);
        if(Bt->Type == 's'){
            AddBlock(DotFl,Bt,"Space",DiskSize);
        }
        if(Bt->Type == 'p'){
            char* Nm = Concat_Izq_with_Der(newString("Primary: "),Bt->PartName,'s','s');
            AddBlock(DotFl,Bt,Nm,DiskSize);   
        }

        if(Bt->Type == 'e'){
            char* Nm = Concat_Izq_with_Der(newString("Extended: "),Bt->PartName,'s','s');
            AddExtended_Block(DotFl,Bt,Nm,DiskSize,Bt->LgParts->Length);   
        }

        if(Bt->Type == 'm'){
            AddBlock(DotFl,Bt,"MBR",DiskSize);   
        }
    }
}

void GenerateDiskRender(char* CompletePathDir,char* ReportPath,char* ReportName){
    //(^< ............ ............ ............   J O I N :   R E P O R T P A T H   &   R E P O R T N A M E
    char* CompleteReportPathDir = Concat_Izq_with_Der(ReportPath,ReportName,'s','s');
    char* dskname = Path_Get_FileName(CompletePathDir);

    //(^< ............ ............ ............   D I S K   L O A D
    MBR* Disk = LoadMBR(CompletePathDir);

    //(^< ............ ............ ............   R E P O R T
    CreatePathDir(ReportPath);

    FILE* DotFl = fopen(CompleteReportPathDir,"w+");

    //(^< ............ ............ ...........   D O T   F I L E
    if(DotFl){
        fprintf(DotFl,"digraph test {\n");
            fprintf(DotFl,"\tnode[shape=plaintext];\n");
            fprintf(DotFl,"\tDiskStruct\n");
            fprintf(DotFl,"\t[\n");

            fprintf(DotFl,"\t\tlabel = \n");

                fprintf(DotFl,"\t\t<\n");

                    fprintf(DotFl,"\t\t\t<TABLE border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">\n");
                
                        fprintf(DotFl,"\t\t\t\t<TR>\n");
                            fprintf(DotFl,"\t\t\t\t<TD bgcolor=\"#ccccff\" height=\"50\" colspan=\"1\">\n");
                                fprintf(DotFl,"%s",dskname);
                            fprintf(DotFl,"\t\t\t\t</TD>\n");
                        fprintf(DotFl,"\t\t\t\t</TR>\n");

                        fprintf(DotFl,"\t\t\t\t<TR>\n");
                        //(^< ............ ............ ........... R E C O R R I D O
                        DoublyGenericList* btList = getBatchList_FromDisk(CompletePathDir,Disk);
                        
                        AddBatch(DotFl,btList,Disk->mbr_tamano);
                        
                        fprintf(DotFl,"\t\t\t\t</TR>\n");

                    fprintf(DotFl,"\t\t\t</TABLE>\n");

                fprintf(DotFl,"\t\t>,\n");

            fprintf(DotFl,"\t];\n");

        fprintf(DotFl,"}");
    }

    fclose(DotFl);
    char* Tmp = newString("xdg-open ");
    Tmp = Concat_Izq_with_Der(Tmp,CompleteReportPathDir,'s','s');
    system(Tmp);

    char* alt = newString("dot -Tpng ");
    alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');
    alt = Concat_Izq_with_Der(alt,newString(" "),'s','s');
    alt = Concat_Izq_with_Der(alt,newString(" -o "),'s','s');

    int ln = strlen(CompleteReportPathDir);
    CompleteReportPathDir[ln - 1] = 'g';
    CompleteReportPathDir[ln - 2] = 'n';
    CompleteReportPathDir[ln - 3] = 'p';
    alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');

    system(alt);


}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ M B R
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void Add_Separator(FILE* DotFl){
    fprintf(DotFl,"\t\t\t\t<TR>\n");
        fprintf(DotFl,"\t\t\t\t\t<TD width = \"150\" colspan=\"2\">\n");
            fprintf(DotFl,"\t\t\t\t\t\t*** *** *** *** *** ***<br/>\n");
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    fprintf(DotFl,"\t\t\t\t</TR>\n");
}

void AddTopTittle(FILE* DotFl,char* TopTittle){
    fprintf(DotFl,"\t\t\t\t<TR>\n");
        fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=\"#a3c2c2\" width = \"150\" colspan=\"2\">\n");
            fprintf(DotFl,"\t\t\t\t\t\t- %s -<br/>\n",TopTittle);
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");
    fprintf(DotFl,"\t\t\t\t</TR>\n");
}

void AddParamValue(FILE* DotFl,char* Color,char* ParamName,char* StringValue){
    fprintf(DotFl,"\t\t\t\t<TR>\n");

        fprintf(DotFl,"\t\t\t\t\t<TD bgcolor=%s width = \"150\">\n",Color);
            fprintf(DotFl,"\t\t\t\t\t\t%s<br/>\n",ParamName);
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");

        fprintf(DotFl,"\t\t\t\t\t<TD width = \"150\">\n");
            fprintf(DotFl,"\t\t\t\t\t\t%s<br/>\n",StringValue);
        fprintf(DotFl,"\t\t\t\t\t</TD>\n");

    fprintf(DotFl,"\t\t\t\t</TR>\n");
}

void AddMBRBlock(FILE* DotFl,MBR* Bf){
    char* Color = newString("\"#00cc99\"");
    Add_Separator(DotFl);
    AddTopTittle(DotFl,"MBR");
    AddParamValue(DotFl,Color,"mbr_tamano",toString(&Bf->mbr_tamano,'i'));
    AddParamValue(DotFl,Color,"mbr_fecha_creacion",toString(Bf->mbr_fecha_creacion,'s'));
    AddParamValue(DotFl,Color,"mbr_disk_signature",toString(&Bf->mbr_disk_signature,'i'));
    AddParamValue(DotFl,Color,"disk_fit",toString(&Bf->disk_fit,'c'));
    Add_Separator(DotFl);
}

void AddEBRBlock(FILE* DotFl,EBR* Er){

    char* Color = newString("\"#ff9900\"");

    char* EBR_Name = Concat_Izq_with_Der(newString("EBR: "),Er->part_name,'s','s');

    Add_Separator(DotFl);
    AddTopTittle(DotFl,EBR_Name);
    AddParamValue(DotFl,Color,"part_status",toString(&Er->part_status,'c'));
    AddParamValue(DotFl,Color,"part_fit",toString(&Er->part_fit,'c'));
    AddParamValue(DotFl,Color,"part_start",toString(&Er->part_start,'i'));
    AddParamValue(DotFl,Color,"part_size",toString(&Er->part_size,'i'));
    AddParamValue(DotFl,Color,"part_next",toString(&Er->part_next,'i'));
    AddParamValue(DotFl,Color,"part_name",Er->part_name);
    Add_Separator(DotFl);
}

void AddPartitionBlock(FILE* DotFl,Partition Prt){

    char* Color = newString("\"#c6ff1a\"");

    char* Part_Name = Concat_Izq_with_Der(newString("Partition: "),Prt.part_name,'s','s');

    Add_Separator(DotFl);
    AddTopTittle(DotFl,Part_Name);
    AddParamValue(DotFl,Color,"part_status_",toString(&Prt.part_status,'c'));
    AddParamValue(DotFl,Color,"part_type_",toString(&Prt.part_type,'c'));
    AddParamValue(DotFl,Color,"part_fit_",toString(&Prt.part_fit[0],'c'));
    AddParamValue(DotFl,Color,"part_start_",toString(&Prt.part_start,'i'));
    AddParamValue(DotFl,Color,"part_size_",toString(&Prt.part_size,'i'));
    AddParamValue(DotFl,Color,"part_name_",Prt.part_name);
    Add_Separator(DotFl);
}

void Generate_MBR_Report(char* CompletePathDir,char* ReportPath,char* ReportName){
    //(^< ............ ............ ............   J O I N :   R E P O R T P A T H   &   R E P O R T N A M E
    char* CompleteReportPathDir = Concat_Izq_with_Der(ReportPath,ReportName,'s','s');
    char* DiskName = Path_Get_FileName(CompletePathDir);

    //(^< ............ ............ ............   D I S K   L O A D
    MBR* Disk = LoadMBR(CompletePathDir);

    //(^< ............ ............ ............   R E P O R T
    CreatePathDir(ReportPath);

    FILE* DotFl = fopen(CompleteReportPathDir,"w+");

    //(^< ............ ............ ...........   D O T   F I L E
    if(DotFl){
        fprintf(DotFl,"digraph test {\n");
            fprintf(DotFl,"\tnode[shape=plaintext];\n");
            fprintf(DotFl,"\tDiskStruct\n");
            fprintf(DotFl,"\t[\n");

            fprintf(DotFl,"\t\tlabel = \n");

                fprintf(DotFl,"\t\t<\n");

                    fprintf(DotFl,"\t\t\t<TABLE border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">\n");
                        //fprintf(DotFl,"\t\t\t\t<TR>\n");
                        //(^< ............ ............ ........... R E C O R R I D O
                        AddTopTittle(DotFl,DiskName);
                        AddMBRBlock(DotFl,Disk);

                        int cnt = 0;
                        while(cnt < 4){
                            if(Disk->mbr_partition[cnt].part_start != -1){
                                AddPartitionBlock(DotFl,Disk->mbr_partition[cnt]);
                                if(Disk->mbr_partition[cnt].part_type == 'e'){

                                    DoublyGenericList* btList = getBatchList_FromDisk(CompletePathDir,Disk);
                                    Batch* ext = getExtended_Batch(btList);

                                    while(ext->LgParts->Length > 0){
                                        Batch* tmp = (Batch*)(DeQueue(ext->LgParts));

                                        if(tmp->Type == 'q'){
                                            EBR* Er = LoadEBR(CompletePathDir,tmp->StartByte);
                                            AddEBRBlock(DotFl,Er);
                                        }
                                    }

                                }
                            }
                            cnt++;
                        }

                        //fprintf(DotFl,"\t\t\t\t</TR>\n");

                    fprintf(DotFl,"\t\t\t</TABLE>\n");

                fprintf(DotFl,"\t\t>,\n");

            fprintf(DotFl,"\t];\n");

        fprintf(DotFl,"}");
    }

    fclose(DotFl);
    char* Tmp = newString("xdg-open ");
    Tmp = Concat_Izq_with_Der(Tmp,CompleteReportPathDir,'s','s');
    system(Tmp);

    char* alt = newString("dot -Tpng ");
    alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');
    alt = Concat_Izq_with_Der(alt,newString(" "),'s','s');
    alt = Concat_Izq_with_Der(alt,newString(" -o "),'s','s');

    int ln = strlen(CompleteReportPathDir);
    CompleteReportPathDir[ln - 1] = 'g';
    CompleteReportPathDir[ln - 2] = 'n';
    CompleteReportPathDir[ln - 3] = 'p';
    alt = Concat_Izq_with_Der(alt,CompleteReportPathDir,'s','s');

    system(alt);

}

#endif // F1_REP