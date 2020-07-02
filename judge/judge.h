#pragma once

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

extern char codeName[];
extern char fileName[];
extern char codeAddress[];
extern char fileAddress[];
int timeLimit;


int compareFile(FILE *, FILE *);

void judgeProcces();

