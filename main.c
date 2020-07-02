#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.c"
#include "judge.c"

#define MAXCHAR 1000

/**
* This function check if the number of inputs & outputs are equal or not.
* @param folderOfTestCases name of test cases folder.
* @return integer 0(zero) if the number of inputs & outputs aren't equal else the number of test cases.
*/
int check(char folderOfTestCases[]){

    int numberOfInputs = countInputs(folderOfTestCases, "in");
    int numberOfOutputs = countInputs(folderOfTestCases, "out");

    if (numberOfInputs == numberOfOutputs)
        return numberOfInputs;

    return 0;
}

int main(){

    char folderOfTestCases[MAXCHAR];
    char fileName[MAXCHAR];
    int numberOfTestCases;

    printf("\n%60s\n","*-*-* Hello *-*-*");
    printf("\n--Please put the folder of inputs & outputs next to this file--\n");
    system("pause");

    while(1){

        system("cls");
        printf("\n--Please enter the name of test cases folder--\n");
        scanf("%s",folderOfTestCases);
        numberOfTestCases = check(folderOfTestCases);
        if (numberOfTestCases != 0 )
            break;
    }

    while(1){

        system("cls");
        printf("\n--Please enter the name of file--\n");
        scanf("%s", fileName);

        int valid = generator(fileName, folderOfTestCases, numberOfTestCases);

        if (valid == 0) {
            system("cls");
            printf("\n--Compile Error!--\n");
            system("pause");
        }
        else
            break;
    }

    char outPutFile[MAXCHAR];
    strcpy(outPutFile, fileName);
    strcat(outPutFile, "Output");

    int numberOfTrueTestCases = judge(folderOfTestCases, outPutFile, numberOfTestCases);
    FILE* answers = fopen("finalResult.txt", "r");

    system("cls");

    for(int i=0; i<numberOfTestCases; i++){
        char result[MAXCHAR];
        fscanf(answers, "%s", result);
        printf(" Test Case #%d  :   %s\n", i+1, result);
    }

    printf(" Number of *true* test cases: %d\n", numberOfTrueTestCases);
    printf(" Number of *false* test cases: %d\n", numberOfTestCases-numberOfTrueTestCases);
    printf(" And your final score is: %d\n", (numberOfTrueTestCases/numberOfTestCases)*100 );
    printf("\n%60s\n","Good Luck >_<");

    system("pause");

    return 0;
}

