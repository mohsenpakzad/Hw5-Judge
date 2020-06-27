#include "generator.h"

/** 
 * This function checks feed of generator to meet the requirements
 * 
 * @param filePAth is the path of feed of generator
 *
 * @return integer 0 in case generator's feed meets standards and requirements , also prints result of failures on screen
 *
 */

int checkFormat(const char filePath[]){ // validation
	return 0;
}

/** 
 * This function copies content of second file into first file
 * 
 * @param filePAth is the path of feed of generator
 *
 * @return integer 0 in case generator's feed meets standards and requirements , also prints result of failures on screen
 *
 */

int generator(const char filePath[]){
	int compileStatus=-1; // 0 for ok
	int fileFormatError=-1; // 0 for ok
	int numberOfInputs,copyResult;
	char testCaseDir[50],testCaseDirIn[50],testCaseDirOut[50],cmd[100],strNumber[4],buffer[100],completeFilePath[100],temp[MAX_ARRAY_SIZE];
	char initialPath[100];
	strcpy(initialPath,getcwd(buffer, sizeof(buffer)));
	strcpy(testCaseDir,filePath);
	strcat(testCaseDir,"/../testcases");
	strcpy(testCaseDirIn,testCaseDir);
	strcpy(testCaseDirOut,testCaseDir);
	strcat(testCaseDirIn,"/inputs");
	strcat(testCaseDirOut,"/outputs");
	fileFormatError=checkFormat(filePath);
	if(fileFormatError==0){ // checking for validation of path file given
		strcpy(completeFilePath,filePath);
		strcat(completeFilePath,"/code.c");
		strcpy(buffer,filePath);
		strcat(buffer,"/code.exe"); // place and name of result exe file
		compileStatus=compile(completeFilePath,buffer);
		strcpy(buffer,filePath);
		strcat(buffer,"/in");
		numberOfInputs=numberOfFiles(buffer);
	}
	else{
		changeColor(RED);
		printf("file format Error\nFormat is not correct...\n");
		changeColor(WHITE);
		pressAnyKey();
		getch();
		return -1;
	}
	if(compileStatus==0){
		changeColor(GREEN);
		printf("Compiled succesfully.\n");
		changeColor(WHITE);
		pressAnyKey();
		getch();
		mkdir(testCaseDir);
		mkdir(testCaseDirIn);
		mkdir(testCaseDirOut);
		int i;
		chdir(filePath);
		system("cls");
		for(i=0;i<numberOfInputs;i++){ // generating ouput from given code
			strcpy(cmd,"code.exe <in/");
			itoa(i+1,strNumber,10);
			strcat(cmd,strNumber);
			strcat(cmd,".txt >../testcases/outputs/output");
			strcat(cmd,strNumber);
			strcat(cmd,".txt");
			puts(cmd);
			system(cmd);
			//system("code.exe <in/1.txt >../testcases/outputs/1.txt"); // sample
		}
		// assume every output is ok :
		for(i=0;i<numberOfInputs;i++){ // loop to create input files in testcase folder
			itoa(i+1,strNumber,10);
			strcpy(temp,"in/");
    		strcat(temp,strNumber);
    		strcat(temp,".txt");
    		strcpy(buffer,"../testcases/inputs/input");
    		strcat(buffer,strNumber);
    		strcat(buffer,".txt");
			copyResult=copyFile(buffer,temp);
			if(copyResult==-1){
				changeColor(RED);
				printf("Error accured ...\n");
				printf("Failed to copy inputs to testcase folder.");
				changeColor(WHITE);
				pressAnyKey();
				getch();
				return -1;
			}	
		}
		if (remove("code.exe") != 0) {
			changeColor(RED);
			printf("Unable to delete the exe file ...");
			changeColor(WHITE);
			getch();
		}
		chdir(initialPath);
		system("cls");
		changeColor(GREEN);
		printf("Done.\n");
		changeColor("w");
		pressAnyKey();
		getch();
		system("cls");
	}
	else{
		changeColor(RED);
		printf("\nCompile failed.\n");
		changeColor(WHITE);
		pressAnyKey();
		getch();
		return -1;
	}
}
