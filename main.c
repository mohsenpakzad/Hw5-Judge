#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator\generator.h"
#include "judge\judge.h"
#define MAX_PATH_SIZE 1000
#define MAX_INPUT_SIZE 100000

/**
* global variable to store EOT or END command, or each line of testcases
*/
char input[MAX_INPUT_SIZE];

/**
* global variable to store path of inputed exe file
*/
char exeFile[MAX_PATH_SIZE];

/**
* function to compile a file using cmd shell and gcc
*
* @return integer 1 if file compiled successfully, 0 if not
*/
int compile() {
	char command[MAX_PATH_SIZE], fileName[MAX_PATH_SIZE], exeName[MAX_PATH_SIZE];
	
	while (1) {
		gets(fileName);
		strcpy(exeName, fileName);
		strcat(fileName, ".c");

		if (doesExist(fileName)) { //file exist to compile
			sprintf(command, "gcc %s -o %s", fileName, exeName);
			system(command);
			
			sprintf(exeFile, "%s.exe", exeName);
			
			if (doesExist(exeFile)) { //there is no compile errors
				puts("\n******************************\n* File compiled successfully *\n******************************\n");
				return 1;
			}
			return 0;
		} else //file not exist to compile
			puts("\n>>> File does not exist! Please check the file name and try again:");
	}
}

/**
* main function
*
* @return integer 0 if there was no error
*/
int main() {
	int len;
	puts(">>> Enter the c file name for generating correct outputs: (don't add .c at the end)");
	
	if (compile()) {
		len = generator();
		puts("\n>>> Enter the c file name that is going to be tested: (don't add .c at the end)");
		
		if (compile())
			judge(len);
		else
			puts("\nTesting file didn't compile successfully :(");
	}
	else
		puts("\nMain file didn't compile successfully :(");

	return 0;
}
