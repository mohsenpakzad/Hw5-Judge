#include "judge.h"

// define your functions and global variables here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <generator.c>

#define MAXCHAR 1000

int check(char folderOfTestCases[]){
    int numberOfInputs = countInputs(folderOfTestCases, "in");
    int numberOfOutputs = countInputs(folderOfTestCases, "out");
    if (numberOfInputs == numberOfOutputs)
        return numberOfInputs;
    return 0;
}

int main()
{
    char folderOfTestCases[MAXCHAR];
    char fileName[MAXCHAR];
    int numberOfTestCases;

    printf("*-*-* Hello *-*-*");
    printf("--Please put the folder of inputs & outputs next to this file--")

    while(1){
        system("cls");
        printf("--Please enter the name of test cases folder--\n");
        scanf("%s",folderOfTestCases);
        numberOfTestCases = check(folderOfTestCases);
        if (numberOfTestCases != 0 )
            break;
    }

    while(1){
        system("cls");
        printf("--Please enter the name of file--\n");
        scanf("%s", fileName);
        int valid = generator(fileName, folderOfTestCases);
        if (valid == 0)
            printf("--Compile Error!--\n");
        else
            break;
    }

    char outPutFile[MAXCHAR];
    strcpy(outPutFile, fileName);
    strcat(outPutFile, "Output");

    char answers[] = "finalResult.txt";
    int numberOfTrueTestCases = judge(folderOfTestCases, outPutFile, numberOfTestCases);

    system("cls");
    for(int i=0; i<numberOfTestCases; i++){
        char result[MAXCHAR];
        fscanf(answers, "%s", result);
        printf("Test Case #%d: %s\n", i+1, result);
    }

    printf("Number of *true* test cases: %d\n", numberOfTrueTestCases);
    printf("Number of *false* test cases: %d\n", numberOfTestCases-numberOfTrueTestCases);
    printf("And your final score is: %d%", (numberOfTrueTestCases/numberOfTestCases)*100 );
    printf("Good Luck >_<");

    return 0;
}
