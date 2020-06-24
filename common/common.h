#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int menuSelect();
int compile(char *filePath,char *exeName);
void showPath();
int numberOfFiles(const char * filePath);
int checkEmptyFile(const char *filePath);
void pressAnyKey();
int checkDir(const char * dirPath);
