#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000

extern char exeFile[];

/**
* function to compare 2 files, ignoring white spaces at the end of file and each line
*
* @param pointer to first file
* @param pointer to second file
* @return integer 1 if both files were equal, 0 if not
*/
int compareFile(FILE* fPtr1, FILE* fPtr2) {
	char ch1, ch2;
	
	while (1) {
		// input character from both files
		ch1 = fgetc(fPtr1);
		ch2 = fgetc(fPtr2);
		
		if (ch1 == EOF || ch2 == EOF)
			break;
		
		if (ch1 == '\n') {
			while (ch2 != '\n') {
				if (ch2 != ' ' && ch2 != '\t')
					return 0;
				ch2 = fgetc(fPtr2);
			}
		} else if (ch2 == '\n') {
			while (ch1 != '\n') {
				if (ch1 != ' ' && ch1 != '\t')
					return 0;
				ch1 = fgetc(fPtr1);
			}
		}
		// if characters are not the same then return 0
		if (ch1 != ch2)
			return 0;
	}
	
	if (ch1 == EOF)
		while (ch2 != EOF) {
			if (ch2 != '\n' && ch2 != ' ' && ch2 != '\t')
				return 0;
			ch2 = fgetc(fPtr2);
		}
	else
		while (ch1 != EOF) {
			if (ch1 != '\n' && ch1 != ' ' && ch1 != '\t')
				return 0;
			ch1 = fgetc(fPtr1);
		}
	// if both files have reached end
	return 1;
}

/**
* function to judge a c file using generated testcases in generator function
*
* @param number of testcases
*/
void judge(int counter) {
	int i, correct = 0;
	puts("Details:");
	
	for (i = 1; i < counter; i++) {
		// running & giving input to exe file
		char command[MAX_SIZE], mainOutputPath[MAX_SIZE];
		sprintf(mainOutputPath, ".\\out\\output%d.txt", i);
		sprintf(command, "%s<.\\in\\input%d.txt>temp_output.txt", exeFile, i);
		system(command);

		FILE* newOutput;
		newOutput = fopen("temp_output.txt", "r");
		FILE* lastOutput;
		lastOutput = fopen(mainOutputPath, "r");
		
		printf("test case #%d: ", i);
		if (compareFile(newOutput, lastOutput)) {
			correct++;
			puts("\tPass");
		} else
			puts("\tFail");

		// finally close files to release resources
		fclose(newOutput);
		fclose(lastOutput);
	}
	
	int maxScore;
	puts("\n>>> Enter an integer as maximum score: ");
	scanf("%d", &maxScore);
	printf("\nYour code's final score is %d out of %d\n", correct * maxScore / (counter - 1), maxScore);
}
