#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 100000

/**
 * This function counts the number of inputs.
 *
 * @param testCaseFolderName Folder of test cases
 * @param subFolder (in or out)
 * @return integer as the number of inputs or outputs
 */
int countInputs(char testCaseFolderName[] , char subFolderName[]) {

	char command[BUFFER_SIZE];
	char path[BUFFER_SIZE];
	FILE* outPut;
	int n;

	outPut = _popen("cd", "r");

	int c;
	int i = 0;
	for (i = 0; (c = fgetc(outPut)) != EOF; i++) {
		path[i] = c;
	}

	sprintf(path + i - 1, "\\%s\\%s", testCaseFolderName, subFolderName);

	sprintf(command, "dir /a:-d /s /b \"%s\" | find /c \":\\\"", path);

	outPut = _popen(command, "r");
	fscanf(outPut, "%d", &n);

	_pclose(outPut);

	return n;
	
}


/**
 * This function generates outputs.
 *
 * @param code name of the code file
 * @param testCase name of folder of test cases
 * @param numberOfTestCases number of inputs or outputs
 * @return 0 when the code doesn't compile successfully and return 1 otherwise
 */
int generator(char code[], char testCases[], int numberOfTestCasses) {

	char command[BUFFER_SIZE];

	sprintf(command, "gcc %s -o out", code);

	if (system(command)) {
		return 0;
	}

	sprintf(command, "if exist %sOutput rmdir /Q /S %sOutput", code, code);
	system(command);

	sprintf(command, "mkdir %sOutput", code);
	system(command);

	for (int i = 1; i <= numberOfTestCasses; i++) {

		sprintf(command, ".\\out.exe <%s\\in\\input%d.txt >%sOutPut\\output%d.txt", testCases, i, code, i);
		system(command);
	}

	system("del out.exe");

	return 1;
}
