#include "generator/generator.h"
#include "judge/judge.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BACK 2
#define CODE_EXECUTED_SUCCESSFULLY 0
#define CLEAR_SCREEN system("cls");fflush(stdin);

/** 
 * The use of this function is to produce test cases.
 * @return 1 as succesful or 2 as not succesful  
 */
int generateTestCase(){

    int result;
    result = getInputsPath();

    if (result != CODE_EXECUTED_SUCCESSFULLY){
        return BACK;
    }

    result = compile();
    if (result == BACK){
        return BACK;
    }
      
    generate();

    return 1;
    
}

/** 
 * The use of this function is to compare the produced test cases.
 * @return 1 as succesful or (2 or 0) as not succesful
 */
int judge(){

    int result;
    result = compileJudge();
    if (result == BACK){
        return BACK;
    }

    generateOutputOfJudge();

    compare();

    printResult();

    return 1;
}

/*
* The use of this function is to print menu
*/
void menu(){

    printf("Please enter the number to choose the command:\n1 -> Generate test case\n2 -> Judge\n3 -> Help\n4 -> Exit\n");
}
/** 
 * main function.
 * @return 0 as succesful
 */
int main() {
    while (1){   
        CLEAR_SCREEN
        
        menu();

        int choice;
        scanf("%d",&choice);getchar();

        switch (choice){
        case 1:
            CLEAR_SCREEN
            generateTestCase();
            break;

        case 2:
            CLEAR_SCREEN
            judge();
            break;
        
        case 3:
            //open the source code and see helps and instructions
            system("start https://github.com/AmirHosein-Gharaati/Hw5-Judge");
            break;
        case 4:
            return 0;

        default:
            break;
        }
    }
    return 0;
}