#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PATH_SIZE 100
#define MAX_COMMAND_SIZE 1000

int doesExist(const char* name);
int generatorFromFile();
int generatorFromCMD();
int generator();
