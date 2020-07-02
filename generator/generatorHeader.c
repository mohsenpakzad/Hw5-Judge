#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generatorHeader.h"

int generator(const char fileAdress[ADRESS_ARRAY_SIZE])
{
  //moveToAnAddress(inOutAdress);
  if (judgeCompile(fileAdress) == NO)
    return NO;
  int i = 1, numberOfTestCases = inFileCounter("TestCase/Input", ".in");
  if (numberOfTestCases == -1)
  {
    printf("  \n%s\n\n", YEL "WARNING:" RESET "  generation process has malfunctioned,\n          Or one of the IO folders has been croupted.\n          You can try running " MAG "Generator" RESET " module again");
    return -1;
  }

  while (i <= numberOfTestCases)
  {
    char strNum[ADRESS_ARRAY_SIZE / 4];
    sprintf(strNum, "%d", i); //int i into string

    //create input name => "input\\in(number).in"
    char inputName[20];
    strcpy(inputName, "TestCase/Input/");
    strcat(inputName, strNum);
    strcat(inputName, ".in");

    //create output name => "output/out(number).in"
    char outputName[20];
    strcpy(outputName, "TestCase/Output/");
    strcat(outputName, strNum); //add number to output name
    strcat(outputName, ".out"); //add .out to output name

    giveInputToCodeAndSaveOutput("/usr/local/adjudicator/temp/gavel", inputName, outputName);

    i++;
  }
  return YES;
}
