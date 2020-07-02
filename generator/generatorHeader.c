#include "../globalHeader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void giveInputToCodeAndSaveOutput(char codeAddress[],char inputAddress[],char outputAddress[]){
  char linuxCode[300+6];
  strcpy(linuxCode, codeAddress);
  strcat(linuxCode, " < ");
  strcat(linuxCode, inputAddress);
  strcat(linuxCode, " > ");
  strcat(linuxCode, outputAddress);
  //linuxCode = "codeAddress < inputAddress > outputAddress"
  system(linuxCode); 
}  

/**
 * fucntion compiles judge file and puts it into temp for further use
 * @param fileAdress address of judge file
 * @return 1 for YES and ) for no
 */
int judgeCompile(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    char argument[2 * ADRESS_ARRAY_SIZE];
    system("rm -rf /usr/local/adjudicator/temp/gccLog.txt 2> /dev/null");
    //system("touch /usr/local/adjudicator/temp/judgeCompilerLog.txt");
    strcpy(argument, "gcc -o gavel ");
    strcat(argument, fileAdress);
    system("touch /usr/local/adjudicator/temp/gccLog.txt");
    strcat(argument, " 2> /usr/local/adjudicator/temp/gccLog.txt");
    system(argument);

    FILE *ptr;
    ptr = fopen("/usr/local/adjudicator/temp/gccLog.txt", "r");

    char character;
    character = fgetc(ptr);
    if (character != EOF) // see if ther is actually a complaint
    {
        printf("\n\n%s ", YEL "Compiler complaint:" RESET);

        while (character != EOF) // print content of complaint
        {
            printf("%c", character);
            character = fgetc(ptr);
        }
        putchar('\n');
        fclose(ptr);
        return NO; //hey in your module if this returns NO you should terminate your module and return  a termination value to main(NO)
    }


    system("cp gavel /usr/local/adjudicator/temp/");
    system("rm -rf gavel");
    return YES; //turn to yes
}
