#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "Fw/StringHandler.h"
#include "Fw/Helper.h"
#include "Analizer.h"

int main()
{
    
    
    char* JsPath = newString("JS_D1_PRI1_vda1.json");
    char* txtCont = getString_from_File(JsPath);
    txtCont = StringCloneWithOut(txtCont,'\n');
    txtCont = StringCloneWithOut(txtCont,'\t');

    int lg = strlen(txtCont);
    txtCont[lg - 5] = ' ';

    char* POST = newString(9000);
    sprintf(POST,"curl -d '%s' -H \"Content-Type: application/json\" -X POST http://localhost:3000/sync/replicate",txtCont);
    system(POST);
    
    return 0;
    
    /*
    newLine_Flag = 0;
    cmdString    = NULL;
     */
    
    int i = 0;
    while (i < 25){
        UsingDisk_List[i] = *newDisk_in_Use();
        i++;
    }

    Omni = newGLS();

    while (1){
        system("clear");
        printf("\n");        
        printf("(^< ............ ............ ............\n");
        printf("Ready to Execute:\n");
        //char *InputString = CatchCommandLine();
        char *InputString = newString("exec -path=/home/wrm/Desktop/CPP_FS/Calidos.sh");
        //int Rs = strcasecmp(InputString, "exit\n");
        //if (Rs == 0){
            //break;
        //}
        ExecuteComand(InputString);
        break;
    }    
    
    printf("(^< ............ S A L I E N D O ............\n");
    return 0;
}
