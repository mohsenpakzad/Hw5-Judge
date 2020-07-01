#pragma once
#include <errno.h>
#include "../mainGlobal.h"

int compareFiles(const char path1[],const char path2[]);
int checkFormatJudge (const char filePath[]);
int judge(const char filePath[],char codePath[]);
