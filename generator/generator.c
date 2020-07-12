#include "generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CODE_EXECUTED_SUCCESSFULLY 0
#define CODE_DID_NOT_EXECUTE 1
#define BACK 2
#define CLEAR_SCREEN system("cls");fflush(stdin);

/** 
 * This function using for removing back slash n
 * @param arr The array to remove '\n' within
 */
void removeBackSlashN(char arr[]){

    int j;
    for (j=0;j<100;j++){
        if (arr[j] == '\n'){
            arr[j] = '\0';
        }
    }
}

/** 
 * The use of this variable is to store the main code name.
 */
char mainCodeName[100];

/** 
 * The use of this function is to compile the main code.
 * 
 * @return 0 if code executed succesfully
 */
int compile(){

    while (1){
        printf("Please enter the main C-file path(Enter \'d\' for the default path): ");
        gets(mainCodeName);

        if (strcmp("back", mainCodeName) == 0){
            system("cls");
            return BACK;
        }

        if (strcmp("d", mainCodeName) == 0){
            strcpy(mainCodeName, "main\\CFileForGenerator\\*.c");
            CLEAR_SCREEN
        }
        
        char compileCommand[100];
        sprintf(compileCommand, "gcc %s -o generator\\generate", mainCodeName);

        int result;
        result = system(compileCommand);
        
        if (result == 0){
            printf("Code Compiled Successfully\nPress Enter to continue\n");
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




/** 
 * The use of this function is to store inputs path and names
 * 
 * @return 0 if code executed succesfully
 */
int getInputsPath(){
    
    while (1){
        printf("Enter the path of inputs(Press \'d\' for the default path): ");
        gets(InputsPathsAndNames.inputsPath);

        if (strcmp("back", InputsPathsAndNames.inputsPath) == 0){
            CLEAR_SCREEN
            return BACK;
        }

        if (strcmp("d", InputsPathsAndNames.inputsPath) == 0){
            strcpy(InputsPathsAndNames.inputsPath, "main\\inputs");
            CLEAR_SCREEN
        }
        
        char filesListCommand[1000];
        sprintf(filesListCommand, "dir /b %s", InputsPathsAndNames.inputsPath);

        int result;
        result = system(filesListCommand);

        if (result == CODE_DID_NOT_EXECUTE){
            printf("Please try again\n");
            getchar();
            CLEAR_SCREEN
            continue;
        }
        printf("\nIs the list of inputs correct?(y/n)");

        char yesOrNo[10];
        gets(yesOrNo);

        if (yesOrNo[0] == 'y' || yesOrNo[0] == 'Y' ){
            sprintf(filesListCommand, "dir /b %s > .\\main\\miscellaneous\\outputsName.txt",
            InputsPathsAndNames.inputsPath);
            system(filesListCommand);

            //saving outputs to a file and then remove it
            FILE* file;
            file = fopen(".\\main\\miscellaneous\\outputsName.txt", "r");
            numberOfInputs = 0;

            while (fgets(InputsPathsAndNames.inputsNames[numberOfInputs], 100, file)){
                removeBackSlashN(InputsPathsAndNames.inputsNames[numberOfInputs]);
                numberOfInputs++;

                if (numberOfInputs>MAXIMUM_NUMBER_OF_TEST_CASES){
                    printf("The maximum number of test cases reached!\n");
                    getchar();
                    getchar();
                    CLEAR_SCREEN
                    return CODE_DID_NOT_EXECUTE;
                }
            }
            fclose(file);

            system("del .\\main\\miscellaneous\\outputsName.txt");
            CLEAR_SCREEN
            return CODE_EXECUTED_SUCCESSFULLY;
        }

        else if (yesOrNo[0] == 'n' || yesOrNo[0] == 'N'){
            CLEAR_SCREEN
            continue;
        }

        else{
            printf("You did not enter a correct character !");
            getchar();
            CLEAR_SCREEN
            continue;
        }
    } 
}

/*
 * loading screen for generating results
 * 
 * @param currentState to calculate the percentage
 */
void loadScreen(int currentState) {
    int i;
    char str[] = "                                        ";
    int end = 40 * currentState / numberOfInputs;

    for(i = 0; i < end; i++) {
        str[i] = '=';
    }

    printf("\rGenerating outputs...[%s] %%%d", str, 100 * currentState / numberOfInputs);
}


/** 
 * The use of this function is to generates outputs.
 * 
 * @return 0 if code executed succesfully
 */
int generate(){

    int i;
    //delete previous output files
    system("del /f /q Output\\mainOutput");
    
    //generating test cases
    for(i=0; i< numberOfInputs;i++){
        loadScreen(i+1);
        
        char generatedCommand[1000];
        sprintf(generatedCommand,"generator\\generate.exe <%s\\\"%s\">\"Output\\mainOutput\\Output_of_%s\"",
        InputsPathsAndNames.inputsPath,
        InputsPathsAndNames.inputsNames[i],
        InputsPathsAndNames.inputsNames[i]);

        system(generatedCommand);
    }
    CLEAR_SCREEN

    printf("Outputs generated in \"Output\\mainOutput\" folder.\nPress enter to continue\n");
    getchar();

    return CODE_EXECUTED_SUCCESSFULLY;
}