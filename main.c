#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generator/generator.h"
#include "judge/judge.h"

#define MAX_ADDRESS_SIZE 1000 + 1
#define MAX_NAME_SIZE 100 + 1

#define generating 1
#define judging 0

#define fullAddress 2
#define inDir 1

char codeName[MAX_NAME_SIZE];
char fileName[MAX_NAME_SIZE];
char codeAddress[MAX_ADDRESS_SIZE];
char fileAddress[MAX_ADDRESS_SIZE];
int timeLimit=0;


/**
* usage : whenever we are in the generating operation , the value is integer 1 ;
* and when we are in the judging operation , the value is integer 0.
*/
int currentOpration=judging;




/**
*
* this function has been written to guide the clients and help them with the usage of each option (generator or judge).
* @param : Nothing!!
* @return : Nothing ;).
*/
void guidingClient(){

    system("color 08");
    printf("do you have any idea about how generator and judge works?\ndo you need help? (y/n) : ");

    char answer;
    scanf(" %c",&answer);

    switch (answer){
        case 'y':
            system("cls");
            system("color 09");
            printf("~GENERATE : getting a directory containing input files and original C code.\nthen compiles it and creates a dirctory containing output files.\n\n");
            printf("__________________________<AHM>____________________________\n\n");
            printf("~JUDGE : getting a directory containing input files , output files and students C code.\nthen compiles it and creates a dirctory containing students output files.\n");
            printf("then compares student's output files matching to original outputs and shows the matching percentage.\n\n");
            system("pause");
            break;

        case 'n':
            system("cls");
            system("color 0A");
            printf("so lets get into the program. :) \n\n");
            system("pause");
            break;

        default:
            system("color 04");
            printf("there's no such option in this function :)\n");
            system("pause");
            system("cls");
            guidingClient();

    }
}



/**
* this function has been written to let the clients choose which option they are going to use.
*
* @param : Nothing!!
* @return : Nothing ;).
*/
void generatingOrJudging(){

    system("color 09");
    printf("choose the topic you wanna access to (<g> for Generate and <j> for Judge ) : ");

    char option;

    scanf(" %c",&option);
    switch (option) {

        case 'g':
            system("cls");
            currentOpration = generating;
            break;

        case 'j':

            printf("put timelimit secend : ");
            scanf("%d",&timeLimit);
            system("cls");
            currentOpration = judging;
            break;

        default:
            system("color 04");
            puts("there's no such option in this function :)");
            system("pause");
            system("cls");
            generatingOrJudging();
    }
}

/**
* this function ask the client that wants to  continue the procces or no .
*
* @param : Nothing!!
* @return integer as result to show that continue proccess or finish it ;).
*/
int wantContinue() {

    system("cls");
    system("color 09");
    printf("do you want continue?(y/n) : ");

    char answer;
    scanf(" %c", &answer);
    switch (answer) {
        case 'y':
            return 1;

        case 'n':
            return 0;

        default:
            system("color 40");
            printf("dude , wrong character entered! try again ;) \n");
            system("pause");
            return (wantContinue());
    }
}


void choosingPath(char);
void getFile(int);


/**
* this function getting file with its address.
*
* @param addressType : when the addresstype is fulladdress getting fulladdress from client  ,
 * if addresstype is inDir show that the file is in current directory and getting filename from client,
* and generate or judging code;).
* @return : Nothing ;).
*/
void getFile(int addressType){
    char filesPath[MAX_ADDRESS_SIZE] = "cd ";
    system("cls");
    system("color 09");

    printf("enter file's name : ");
    scanf(" %s", fileName);

    if(addressType==fullAddress) {
        printf("enter the full address of your file : ");
        scanf(" %s", fileAddress);
        sprintf(filesPath,"cd /d %s\\",fileAddress);
    }

    strcat(filesPath, fileName);

    if(system(filesPath) != 0){
        system("color 40");
        system("pause");
        if(wantContinue())
            choosingPath('f');
        else return;
    }
    else {
        if(currentOpration)
            generateProcces();
        else
            judgeProcces();
    }

    return ;
}

/**
* this function gets a code in format ".c" with its address.
 * @param addressType : when the addrestype is fulladdres getting fulladdress from client  ,
 * if addrestype is inDir show that the file is in current directory and getting filename from client,
* and generate or judging code;).
* @return : Nothing ;).
*/
void getCode(int addressType) {

    system("cls");
    system("color 09");
    printf ("enter the name of c code without using .c (example : main.c --> main) : ");

    char compilingCommand[MAX_ADDRESS_SIZE] = "gcc ";

    scanf(" %s", codeName);
    sprintf(compilingCommand,"gcc %s.c -o %s",codeName,codeName);

    if (addressType== fullAddress) {

        char codesPath[MAX_ADDRESS_SIZE];

        printf("enter full address : ");
        scanf(" %s", codeAddress);
        sprintf(codesPath,"cd /d %s && %s",codeAddress,compilingCommand);
        strcpy(compilingCommand, codesPath);
    }

    system("cls");

    if (system(compilingCommand) != 0) {
        system("color 40");
        system("pause");

        if(wantContinue())
            choosingPath('c');
        else return;
    }

    else {
        system("color 0A");
        printf("compiled successfully! :) \n");
        system("pause");
        system("cls");
    }

    return;
}


/**
* this function checks that we need fullAddress to find the file or file is in the current directory.
*
* @param cfm : when its value is character 'c' choosing the c file path ,
 * when its value is character 'f' choosing the input file path ,
 * when its value is character 'm' choosing the path that client want to create testcases in it  ,
* @return : Nothing ;).
*/

void choosingPath(char cfm){
    system("cls");
    system("color 09");

    if(cfm == 'c')
        printf("is your .c file(which contains your code) in the current directory?(y/n) : ");
    else if(cfm == 'f')
        printf("is your testcase file in the current directory?(y/n) : ");
    else if(cfm == 'm')
        printf("make testcase file here?(y/n) : ");

    char answer;

    scanf(" %c",&answer);

    switch (answer) {

        case 'y':
            if(cfm == 'c')
                getCode(inDir);
            else if(cfm == 'f')
                getFile(inDir);
            else if(cfm == 'm')
                maketastcase(inDir);
            break;

        case 'n':
            if(cfm == 'c')
                getCode(fullAddress);
            else if(cfm == 'f')
                getFile(fullAddress);
            else if(cfm == 'm')
                maketastcase(fullAddress);
            break;

        default:
            system("color 40");
            printf("dude , wrong character entered! try again ;) \n");
            system("pause");
            choosingPath(cfm);

    }
}



/**
* this function let the client to choose between creating testcase or use input files for generating code.
*
* @param :Nothing;).
* @return : Nothing ;).
*/
void howToGenerate(){
    system("cls");
    system("color 09");
    printf("c code with file input(c),c code without file input(m) : ");

    char answer;

    scanf(" %c",&answer);

    switch (answer) {

        case 'c':
            choosingPath('c');
            choosingPath('f');
            break;

        case 'm':
            choosingPath('c');
            choosingPath('m');
            generateProcces();
            break;

        default:
            system("color 40");
            printf("dude , wrong character entered! try again ;) \n");
            system("pause");
            howToGenerate();
    }
}

int main() {

    printf("Hello , welcome to the <AHM> judging program. :) \n\n");

    guidingClient();

    system("cls");

    generatingOrJudging();

    if(currentOpration == generating)
        howToGenerate();

    else {
        choosingPath('c');
        choosingPath('f');
    }


    return 0;
}