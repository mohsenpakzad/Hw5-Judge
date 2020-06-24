//compile function
//dont know what to add to the generatotHeader.c/.h
//debug

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generatorHeader.h"

Compile()
  
int generator(char inOutAdress[],char codeAddress[]){
  MoveToAnAddress(inOutaddress);
  
  int i=1;
  while(i<=numberOfTestCases){  //numberOfTestCases is defined in generatorHeader.h and is given value in main.c
    char strNum[MAX_TEST_CASE]; //MAX_TEST_CASE is defined in generatorHeader.h
    sprintf(strNum, "%d", i); //int i into string
    
    //create input name => "input\\in(number).in"
    char inputName[11];
    strcpy(inputName,"input\\in");
    strcat(inputName, strNum); //add number to input name
    strcat(inputName, ".in"); //add .in to input name
    
    //create output name => "output\\out(number).in"
    char outputName[12];
    strcpy(outputName,"output\\out");
    strcat(outputName, strNum); //add number to output name
    strcat(outputName, ".out"); //add .out to output name
    
    GiveInputToCodeAndSaveOutput(codeAddress, inputName, outputName);
    
    i++;
  }
  return 1;
}
