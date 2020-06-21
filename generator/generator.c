#include "generatorHeader.h"

Compile()
  
int generator(char inOutAdress,char codeAddress[]){
  system("cd inOutAddress");
  
  int i=1;
  while(1){
    char strNum[MAX_TEST_CASE];
    sprintf(strNum, "%d", i); //int i into string
    
    //create input name
    char inputName[11];
    strcpy(inputName,"input//");
    strncat(inputName, strNum, 4); //add number to input name
    strncat(inputName, ".in", 3); //add .in to input name
    //create output name
    char outputName[12];
    strcpy(outputName,"output//");
    strncat(outputName, strNum, 4); //add number to output name
    strncat(outputName, ".out", 4); //add .out to output name
    system("codeAddress < inputName > outputname");
    
    i++;
  }
}

// define your functions and global variables here
