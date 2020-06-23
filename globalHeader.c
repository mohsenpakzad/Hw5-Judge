#include <stdio.h>
#include "globalHeader.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int testCaseViewState = 0; //variable to check if show caseing results int terminal is needed 0 means No , 1 Yes

char logAddress[ADRESS_ARRAY_SIZE] = " ";
char judgeFileAdress[ADRESS_ARRAY_SIZE] = " ";
char inOutFileAdress[ADRESS_ARRAY_SIZE] = " ";
char suspectFileAdress[ADRESS_ARRAY_SIZE] = " ";

int typeCExist(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    int extensionPtr;

    if ((extensionPtr = strstr(fileAdress, ".c") != NULL) && (fileAdress[strlen(fileAdress) - 1] == 'c'))
    {
        return YES;
    }
    else
        return NO;
}
int dirExist(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    // Creating a directory
    if (mkdir(fileAdress, 0777) == -1)
        return YES;

    else
        return NO;
}
int ioFileCounter(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    int ioFileCount = -1;

    system("ls -1 *.in | wc -l > /usr/local/temp/fileCount.txt");
    FILE *ptr = fopen("/usr/local/temp/fileCount.txt", "r");
    fscanf(ptr, "%d", &ioFileCount);
    fclose(ptr);
    system("rm -f /usr/local/temp/fileCount.txt");

    return ioFileCount;
}
