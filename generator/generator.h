#pragma once
#include "../mainGlobal.h"

int generator(const char filePath[]);
int checkFormat(const char filePath[]);
int endsWith(const char str[], const char suffix[]);
int checkInputs(char inputs[][5], int inputsLen);
int isNumerical(const char number[]);
