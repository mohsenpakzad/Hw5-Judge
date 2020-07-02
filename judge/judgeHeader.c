#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../globalHeader.h"
/** 
*function compiles suspect file
*@param adress of files that needs to be tested
*@return an int show if function ran without error
*/
int suspectCompile(char fileAdress[ADRESS_ARRAY_SIZE]){
    char argument[2 * ADRESS_ARRAY_SIZE];
    system("rm -rf /usr/local/adjudicator/temp/resHold 2> /dev/null");
    system("rm -rf suspect 2> /dev/null");
    system("rm -rf /usr/local/adjudicator/temp/suspectLog.txt 2> /dev/null");
    //system("touch /usr/local/adjudicator/temp/judgeCompilerLog.txt");
    strcpy(argument, "gcc -o suspect ");
    strcat(argument, fileAdress);
    system("touch /usr/local/adjudicator/temp/suspectLog.txt");
    strcat(argument, " 2> /usr/local/adjudicator/temp/suspectLog.txt");
    system(argument);

    FILE *ptr;
    ptr = fopen("/usr/local/adjudicator/temp/suspectLog.txt", "r");

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
    system("mkdir /usr/local/adjudicator/temp/resHold"); // make somewhere to put results

    
    return YES; //turn to yes
}
