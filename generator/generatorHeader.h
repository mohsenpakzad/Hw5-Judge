#pragma once
// declare your functions and global variables here

int numberOfTestCases;

void linuxCodeToMoveToAnAddress(char address[]){
   char str[100+3];
  strcpy(str, "cd ");
  strcpy(str, address);
  //str = "cd address"
  system(str);
}
  
void linuxCodeToGiveInputToCodeAndSaveOutput(char codeAddress[],char inputAddress[],char outputAddress[]){
  char linuxCode[300+6];
  strcpy(linuxCode, codeAddress);
  strcat(linuxCode, " < ");
  strcat(linuxCode, inputAddress);
  strcat(linuxCode, " > ");
  strcat(linuxCode, outputAddress);
  //linuxCodeForOutputGeneration = "codeAddress < inputAddress > outputAddress"
  system(linuxCode); 
}
  
