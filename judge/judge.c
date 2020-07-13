#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include"generator.h"
int countOfTestCases;

char s1[100],s2[100],s3[100],s4[100];
/**
* Used for show correct test cases
*/
int correct_testcase;

/**judge function read output files describe and compare this two file groups :
* 1) ref_outputxx.txt (xx is an integer) the output generated by referenceprogram.exe
* 2) test_outputxx.txt (xx is an integer) the output generated by testprogram.exe
*/
int judge(){
/**generator function include in headerfile.h
* this function read reference and test c programs , compile them and generate output file
* with input file to compare with judge function
*/
    countOfTestCases=generator();
    if(countOfTestCases==-1){
        return 0;
    }
/**
* open to compiled output files :
* ref_outputxx.txt (xx is integer number) from ref_output directory generated by referenceprogram.exe
* test_outputxx.txt (xx is integer number) from test_output directory generated by testprogram.exe
*/
    FILE *fp1, *fp2;
    int ch1, ch2;
    printf("------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------please wait judge is running-------------------------------\n");
    printf("------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<countOfTestCases-1;i++){
       strcpy(s1,".\\test_output\\test_output");
       itoa(i+1,s2,10);
        strcpy(s3,".txt");
        strcat(s1,s2);
        strcat(s1,s3);

        fp1 = fopen(s1, "r");
        strcpy(s1,".\\ref_output\\ref_output");
        itoa(i+1,s2,10);
        strcpy(s3,".txt");
        strcat(s1,s2);
        strcat(s1,s3);

        fp2 = fopen(s1, "r");
        ch1 = getc(fp1);
        ch2 = getc(fp2);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)){
            ch1 = getc(fp1);
            ch2 = getc(fp2);
         }

        if (ch1 == ch2){
            printf("Test case %d : Correct\n",i+1);
            correct_testcase+=1;
        }

        else if (ch1 != ch2){
           printf("Test case %d : -False-\n",i+1);
        }

        fclose(fp1);
        fclose(fp2);
    }
    return 1;
}
/**
*This function print number of test cases and calculate percent of them.
*/
void printnum(){
    printf("Correct testcases : %d from %d\n",correct_testcase,(countOfTestCases-1));
    printf("Your score is : %.1f from 100 .\n",((float)correct_testcase/(countOfTestCases-1))*100);
    printf("------------------------------------------------------------------------------------------------\n");
}

void main(){
    printf("------------------------------------------------------------------------------------------------\n");
    printf("Welcome to judge program .\n");
    printf("please put your input test cases in input folder on seperate files( like input1.txt etc...) . \n");
    printf("Notice : Please put all C programs (reference & test ) file in judge program directory\n");
    printf("------------------------------------------------------------------------------------------------\n");
    if(judge()){
        printf("-------------------------------------------Judge Result   --------------------------------------\n");
        printnum();
    }

    system("pause");
}


