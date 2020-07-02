#include "../globalHeader.h"
#define MAX_TEST_CASE 1000

#pragma once

int numberOfTestCases;
void moveToAnAddress(char address[]);
void giveInputToCodeAndSaveOutput(char codeAddress[], char inputAddress[], char outputAddress[]);
int judgeCompile(const char fileAdress[ADRESS_ARRAY_SIZE]);

