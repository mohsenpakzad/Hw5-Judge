#include "judge.h"
#include "../generator/generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CODE_EXECUTED_SUCCESSFULLY 0
#define CODE_DID_NOT_EXECUTE 1
#define BACK 2
#define CLEAR_SCREEN system("cls");fflush(stdin);

/*
 * The use of this variable is to store results of compare function
*/
char judgeResult[MAXIMUM_NUMBER_OF_TEST_CASES];

/** 
 * The use of this variable is to store code name for judge
 */
char mainCodeNameJudge[100];


/** 
 * The use of this function is to compile user code.
 * 
 * @return 0 if code executed succesfully
 */
int compileJudge(){

    while (1){
        printf("Please enter the user C-File path(Press \'d\' for the default path): ");
        gets(mainCodeNameJudge);

        if (strcmp("back", mainCodeNameJudge) == 0){
            CLEAR_SCREEN
            return BACK;
        }

        if (strcmp("d", mainCodeNameJudge) == 0){
            strcpy(mainCodeNameJudge, "main\\CFileForJudge\\*.c");
            CLEAR_SCREEN
        }

        char arr[100];
        sprintf(arr, "gcc %s -o judge\\testCode", mainCodeNameJudge);

        int result;
        result = system(arr);

        if (result == 0){
            printf("Code Compiled Successfully\n");
            getchar();
            CLEAR_SCREEN
            return CODE_EXECUTED_SUCCESSFULLY;
        }

        else{
            printf("\nYour code did not compile due to previous errors\nPress Enter to continue\n");
            getchar();
            CLEAR_SCREEN
        }
    }	
}

/*
 * The use of this function is to generate outputs of user(judge)  
 */
void generateOutputOfJudge(){
    
    //delete previous outputs in judgeOuput folder
    system("del /f /q Output\\judgeOutput");

    int i;
    for(i=0;i<numberOfInputs;i++){
        //loading screen
        loadScreen(i+1);

        char generateCommand[200];

        //passing inputs path to testCode.exe and saving output to judgeOuput folder
        sprintf(generateCommand, "judge\\testCode.exe <%s\\\"%s\">\"Output/judgeOutput/Judge_output_of_%s\"", 
        InputsPathsAndNames.inputsPath, 
        InputsPathsAndNames.inputsNames[i],
        InputsPathsAndNames.inputsNames[i]);

        system(generateCommand);
    }
    CLEAR_SCREEN

    printf("Outputs saved into \"Output\\judgeOutput\" folder\nPress Enter to continue\n");
    getchar();
    CLEAR_SCREEN
}

/*
 * loading screen for generating results
 * 
 * @param currentState to calculate the percentage
 */
void judgeLoader(int currentState){
    int i;
    char str[] = "                                        ";
    int end = 40 * currentState / numberOfInputs;

    for(i = 0; i < end; i++) {
        str[i] = '=';
    }

    printf("\rComparing outputs...[%s] %%%d", str, 100* currentState / numberOfInputs);
}

/** 
 * The use of this function is to compare main output and judge output  
 */
void compare(){

    int i;
    int result;

    for ( i = 0; i<numberOfInputs; i++){
        //loading screen
        judgeLoader(i+1);

        char comparedCommand [200];
        sprintf(comparedCommand, "fc \"Output\\mainOutput\\Output_of_%s\" \"Output\\judgeOutput\\Judge_output_of_%s\" > nul",
        InputsPathsAndNames.inputsNames[i],
        InputsPathsAndNames.inputsNames[i]);
        
        result = system(comparedCommand);
        judgeResult[i] = (result == 0) ? '0' : '1';
        
    }

    CLEAR_SCREEN
}

/** 
 * The use of this function is to print and save results
 *   
 */
void printResult(){
    CLEAR_SCREEN

    printf("Do you want to save the results?(y) ");

    FILE *fp;
    
    char ans[10];
    int flag = 0;
    char fileName[50];
    const char *dirName = "result\\";
    gets(ans);

    CLEAR_SCREEN

    if (ans[0] == 'y' || ans[0] == 'Y') {
        flag = 1;
        /*for (i = 0; i < 7; i++)
        {
            fileName[i] = dirName[i];
        }*/

        strcpy(fileName,dirName);

        puts("Please enter the file name:");
        gets(fileName + 7);
        
        strcat(fileName,".txt");

        fp = fopen(fileName, "w");
    }
    CLEAR_SCREEN

    int countAccepteds=0;
    int i;
    for ( i = 0; i<numberOfInputs;i++){
        // 0 == Accepted
        if (judgeResult[i] == '0'){
            countAccepteds++;
            printf("Test Case \"%s\":\n\tAccepted!\n", InputsPathsAndNames.inputsNames[i]);
            if (flag)
                fprintf(fp, "Test Case \"%s\":\n\tAccepted!\n", InputsPathsAndNames.inputsNames[i]);
        }

        // 1 == Wrong answer
        else if (judgeResult[i] == '1'){
            printf("Test Case \"%s\":\n\tWrong Answer!\n", InputsPathsAndNames.inputsNames[i]);
            if (flag)
                fprintf(fp, "Test Case \"%s\":\n\tWrong Answer!\n", InputsPathsAndNames.inputsNames[i]);
        }
    }

    printf("Point : %d/%d", countAccepteds, numberOfInputs);
    
    if (flag){
        fprintf(fp, "Point : %d/%d", countAccepteds, numberOfInputs);
        fclose(fp);
    }
    
    getchar();
    CLEAR_SCREEN
}