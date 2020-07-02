#include <stdlib.h>
#include <stdio.h>
#include "globalHeader.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
/**
 * variable to check if show caseing results int terminal is needed 0 means No , 1 Yes
 */

/**
 * global var to save reuqired paths
 */
char logAddress[ADRESS_ARRAY_SIZE] = " ";
char judgeFileAdress[ADRESS_ARRAY_SIZE] = " ";
char inOutFileAdress[ADRESS_ARRAY_SIZE] = " ";
char suspectFileAdress[ADRESS_ARRAY_SIZE] = " ";

/**
 * function checks if input is a c file or not
 * @param fileAdress files name or path
 * @return 1 for yes and 0 for no
 */
int typeCExist(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    

    if ((strstr(fileAdress, ".c") != NULL) && (fileAdress[strlen(fileAdress) - 1] == 'c'))
    {
        return YES;
    }
    else
        return NO;
}


/**
 * fucntion checks if directory exists or no
 * @param fieAdress files name or path
 * @return 1 for yes and 0 for no
 */
int dirExist(const char fileAdress[ADRESS_ARRAY_SIZE])
{
    // Creating a directory
    if (mkdir(fileAdress, 0777) == -1)
        return YES;

    else
        return NO;
}

/**
 * goes to the given directory and counts all *.txt files
 * @param fieAdress files name or path
 * @return an integer = number of .txt files in the directory if there was problem it returns -1
 */
int inFileCounter(const char fileAdress[ADRESS_ARRAY_SIZE],const char ioExten[4])
{
    int ioFileCount = -1;
    char argument[ADRESS_ARRAY_SIZE];
 
    strcpy(argument,"ls -1 ");
    strcat(argument,fileAdress);
    strcat(argument," | wc -l");
    //strcat(argument,ioExten);
    strcat(argument," > /usr/local/adjudicator/temp/fileCount.txt");
    system(argument); //counts *.txt files and puts the number in specified path
    FILE *ptr = fopen("/usr/local/adjudicator/temp/fileCount.txt", "r");
    fscanf(ptr, "%d", &ioFileCount);
    fclose(ptr);
    system("rm -f /usr/local/adjudicator/temp/fileCount.txt");
    //printf("\n\nio fileCount: %d\n",ioFileCount);
    return ioFileCount;
}

  
