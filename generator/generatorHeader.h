#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEST_CASE 1000

#pragma once

int numberOfTestCases;

void moveToAnAddress(char address[]){
   char str[100+3];
  strcpy(str, "cd ");
  strcpy(str, address);
  //str = "cd address"
  system(str);
}
  
void giveInputToCodeAndSaveOutput(char codeAddress[],char inputAddress[],char outputAddress[]){
  char linuxCode[300+6];
  strcpy(linuxCode, codeAddress);
  strcat(linuxCode, " < ");
  strcat(linuxCode, inputAddress);
  strcat(linuxCode, " > ");
  strcat(linuxCode, outputAddress);
  //linuxCode = "codeAddress < inputAddress > outputAddress"
  system(linuxCode); 
}
  
