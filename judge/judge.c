#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../globalHeader.h"
#include "judgeHeader.h"

int judge(char fileAdress[], int inputCount)
{
    if (suspectCompile(fileAdress) == NO)
        return NO;
    //else suspect is our file
    int count, score = 0;
    char number[10], hostString[MAX_OUTPUT_LENGTH], checkString[MAX_OUTPUT_LENGTH];
    FILE *hostFile, *checkFile;
    putchar('\n');
    for (count = 1; count <= inputCount; count++)
    {
        /*Create Command For CMD!*/
        /*File Structure ---> input1.txt*/

        sprintf(number, "%d", count); //convert int to char.

        char command[2 * ADRESS_ARRAY_SIZE] = "./suspect < TestCase/Input/";
        strcat(command, number);
        strcat(command, ".in > /usr/local/adjudicator/temp/resHold/");
        strcat(command, number);
        strcat(command, ".out");
        system(command);
        char hostFileHold[2 * ADRESS_ARRAY_SIZE];
        char hostFilename[2 * ADRESS_ARRAY_SIZE] = "TestCase/Output/";
        strcat(hostFilename, number);
        strcpy(hostFileHold, hostFilename);
        strcat(hostFileHold, ".txt");
        strcat(hostFilename, ".out");
        strcpy(command, "cp ");
        strcat(command, hostFilename);
        strcat(command, " ");
        strcat(command, hostFileHold);
        system(command);

        char checkFileHold[2 * ADRESS_ARRAY_SIZE];
        char checkFilename[2 * ADRESS_ARRAY_SIZE] = "/usr/local/adjudicator/temp/resHold/";
        strcat(checkFilename, number);
        strcpy(checkFileHold, checkFilename);
        strcat(checkFileHold, ".txt");
        strcat(checkFilename, ".out");
        strcpy(command, "cp ");
        strcat(command, checkFilename);
        strcat(command, " ");
        strcat(command, checkFileHold);
        system(command);

        //printf("host file name %s\n",hostFilename);
        //printf("check file name %s\n",checkFilename);

        hostFile = fopen(hostFileHold, "r");

        while (fgets(hostString, MAX_OUTPUT_LENGTH, hostFile) != NULL)
            ;
        fclose(hostFile);

        checkFile = fopen(checkFileHold, "r");
        while (fgets(checkString, MAX_OUTPUT_LENGTH, checkFile) != NULL)
            ;
        fclose(checkFile);
        if (strcmp(hostString, checkString) == 0)
        {
            printf("\tTest Case #%d: " BGGREEN BLD " Accepted " RESET "\n", count);
            score++;
        }
        else
            printf("\tTest Case #%d: " BGRED BLD " Declined " RESET "\n", count);

        strcpy(command, "rm -rf ");
        strcat(command, hostFileHold);
        system(command);
        strcpy(command, "rm -rf ");
        strcat(command, checkFileHold);
        system(command);
    }
    printf(BLD"\n\t----------------------------\n\tScore: %.2f\n"RESET,(float)(score*100)/inputCount);

    return YES;
}
