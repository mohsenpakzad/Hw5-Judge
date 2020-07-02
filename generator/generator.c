#include "generator.h"

/** 
 * This function checks str is ended with suffix or not
 * 
 * @param str is the main string that should be checked at the end
 * @param suffix is string that should be checked with the end of main string
 *
 * @return integer 0 if str ends with the given suffix otherwise returns 1
 *
 */

int endsWith(const char str[], const char suffix[]){
	int strLen = strlen(str);
	int suffixLen = strlen(suffix);
	int difLen = strLen - suffixLen;
	
	if(difLen < 0)
		return 1;
		
	while(suffixLen >= 0)
		if(str[suffixLen+difLen] != suffix[suffixLen--])
			return 1;
	return 0;
}

/** 
 * This function gets a string and checks if it's all numerical
 * 
 * @param number is the string needed to be checked
 *
 * @return integer 0 if "number" string is numerical otherwise 1
 *
 */

int isNumerical(const char number[]){
	int i=0;
	
	while(number[i])
		if(!isdigit(number[i++]))
			return 1;
	return 0; // 1 for ok
}

/** 
 * This function checks input files in the "in" folder
 * 
 * @param inputs is array of files must be checked
 * @param inputsLen is the len of inputs array
 *
 * @return integer 0 if format of files is correct otherwise 1
 *
 */

int checkInputs(char inputs[][MAX_ARRAY_SIZE], int inputsLen){
	int check[MAX_ARRAY_SIZE], index;
	
	for(index=0; index<inputsLen; index++)
		check[index] = 0;
		
	for(index=0; index<inputsLen; index++){
		if(isNumerical(inputs[index]))
			return 1;
		check[atoi(inputs[index])-1] = 1;
	}
	
	for(index=0; index<inputsLen; index++)
		if(check[index] == 0)
			return 1;
	return 0;
}

/** 
 * This function checks feed of generator to meet the requirements
 * 
 * @param filePath is the path of feed of generator
 *
 * @return integer 0 in case generator's feed meets standards and requirements , also prints result of failures on screen
 *
 */

int checkFormat(const char filePath[]){ // validation
	if(checkDir(filePath)==-1){ // check address validation
		printError("the given path is incorrect...\n");
		return 1;
	}
	chdir(filePath);
	
	char checkFile[MAX_ARRAY_SIZE];
	struct dirent *de; // explained in __generate__ function
	DIR *dr; // DIR pointer for directory search 
	
	int inCheck = 0, codeCheck = 0;
	dr = opendir("."); // pointer to current directory
	while ((de = readdir(dr)) != NULL){
		strcpy(checkFile, de->d_name);
		if(!strcmp(checkFile, "..") || !strcmp(checkFile, "."))	// "." and ".." are directory paths that are always present
			continue;
		else if(!strcmp(checkFile, "in")) // found "in" folder
			inCheck = 1;
		else if(!strcmp(checkFile, "code.c")) // found testcode (code.c)
			codeCheck = 1;
		else if(strcmp(checkFile, "code.exe")){ // other files and folders except executable testcode (code.exe)
			printError("the main folder should only include \"in\" folder and \"code.c\" ...\n");	
			return 1;
		}
	}
	if(inCheck != 1){ // check existence of "in" folder
		printError("the main folder must contain the \"in\" folder...\n");
		return 1;
	}	
	if(codeCheck != 1){ // check existence of "code.c" file
		printError("the main folder must contain the \"code.c\"...\n");
		return 1;
	}
	
	int numberOfInputs = numberOfFiles("in");
	char inputs[numberOfInputs][MAX_ARRAY_SIZE];
	int  inputsLen = 0;
	dr = opendir("in");							
	while ((de = readdir(dr)) != NULL){ // checking the "in" folder should only include ".txt" files
		strcpy(checkFile, de->d_name);
		if(!strcmp(checkFile, "..") || !strcmp(checkFile, "."))	// "." and ".." are directory paths that are always present
			continue;
		else if(endsWith(checkFile, ".txt")){
			printError("the \"in\" folder should only include \".txt\" files...\n");
			return 1;
		}
		checkFile[strlen(checkFile)-4] = '\0';
		strcpy(inputs[inputsLen++], checkFile);
	}
	if(!inputsLen){ // check emptiness of "in" folder
		printError("the \"in\" folder should not be empty...\n");
		return 1;
	}
	if(checkInputs(inputs, inputsLen)){	// checking file names
		printError("file names must be numerical and sorted...\n");
		return 1;	
	}
		
	return 0;
}

/** 
 * This function generates feed for judge module
 * 
 * @param filePAth is the path of feed of generator
 *
 * @return integer -1 in case of failure
 *
 */

int generator(const char filePath[]){
	int compileStatus=-1; // 0 for ok
	int fileFormatError=-1; // 0 for ok
	int numberOfInputs,copyResult;
	char testCaseDir[MAX_ARRAY_SIZE]; // address of "testcases" folder
	char testCaseDirIn[MAX_ARRAY_SIZE]; // address of "inputs" folder
	char testCaseDirOut[MAX_ARRAY_SIZE]; // address of "outputs" folder
	char cmd[MAX_ARRAY_SIZE]; // comman lines for system
	char buffer[MAX_ARRAY_SIZE];
	char completeFilePath[MAX_ARRAY_SIZE]; // address of testcode (code.c)
	char temp[MAX_ARRAY_SIZE];
	char initialPath[MAX_ARRAY_SIZE]; // address of main folder
	strcpy(initialPath, getcwd(buffer, sizeof(buffer)));
	
	fileFormatError = checkFormat(filePath);
	chdir(initialPath);
	if(fileFormatError==0){ // checking for validation of path file given
		sprintf(completeFilePath, "%s/code.c", filePath); // address of testcode (code.c)
		sprintf(buffer, "%s/code.exe", filePath); // address and name of result exe file
		compileStatus = compile(completeFilePath,buffer);
		sprintf(buffer, "%s/in", filePath);
		numberOfInputs = numberOfFiles(buffer);
	}
	else{
		pressAnyKey();
		return -1;
	}
	
	if(compileStatus==0){
		colorMessage(GREEN,"Compiled succesfully.\n",WHITE);
		pressAnyKey();
		
		sprintf(testCaseDir, "%s/../testcases", filePath);
		mkdir(testCaseDir);
		sprintf(testCaseDirIn, "%s/inputs", testCaseDir);
		mkdir(testCaseDirIn);
		sprintf(testCaseDirOut, "%s/outputs", testCaseDir);
		mkdir(testCaseDirOut);
		chdir(filePath);
		system("cls");
		
		int i;
		for(i=0; i<numberOfInputs; i++){ // generating output from given code
			sprintf(cmd, "code.exe <in/%d.txt >../testcases/outputs/output%d.txt", i+1, i+1);			
			puts(cmd);
			system(cmd);
			//system("code.exe <in/1.txt >../testcases/outputs/1.txt"); // sample
		}
		// assume every output is ok :
		showPath();
		
		for(i=0; i<numberOfInputs; i++){ // loop to create input files in testcase folder
			sprintf(temp, "in/%d.txt", i+1);
			puts(temp);
			sprintf(buffer, "../testcases/inputs/input%d.txt", i+1);
			copyResult = copyFile(buffer,temp);
			
			if(copyResult==-1){
				printError("Error accured ...\n");
				printError("Failed to copy inputs to testcase folder.");
				pressAnyKey();
				if (remove("code.exe") != 0) { // try to delete the executable testcode (code.exe)
					printError("Unable to delete the exe file ...");
					getch();
				}
				chdir("..");
				return -1;
			}	
		}
		if (remove("code.exe") != 0) { // try to delete the executable testcode (code.exe)
			printError("Unable to delete the exe file ...");
			getch();
		}
		chdir(initialPath);
		system("cls");
		colorMessage(GREEN, "Done.\n", WHITE);
		pressAnyKey();
		system("cls");
	}
	else{
		printError("\nCompile failed.\n");
		pressAnyKey();
		return -1;
	}
}
