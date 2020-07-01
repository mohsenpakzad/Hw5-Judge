#include "judge.h"

/** 
 * This function compares two files to be exactly identical
 * 
 * @param path1 is the path of first file
 * @param path2 is the path of second file
 *
 * @return integer as result of comparing them , 0 in case they are identical
 *
 */
 
int compareFiles(const char path1[],const char path2[]){
	FILE *file1 = fopen(path1, "r");
	FILE *file2 = fopen(path2, "r");
	if (file1 == NULL || file2 == NULL){
		changeColor(RED);
		printf("Error : Files not open\n");
		changeColor(WHITE);
		return -1;
   }
	char ch1 = getc(file1);
	char ch2 = getc(file2);
	int error = 0, pos = 0, line = 1;
	while (ch1 != EOF && ch2 != EOF){
		pos++;
		if(ch1 == '\n' && ch2 == '\n'){
			line++;
			pos = 0;
		}
		if(ch1 != ch2){
			error++;
		}
		ch1 = getc(file1);
		ch2 = getc(file2);
	}
//	printf("Total Errors : %d\t", error);
	fclose(file1);
	fclose(file2);
	if(error) return -1;
	else return 0;
}

/** 
 * This function checks testcase folder to be standard 
 * kinda vildates the testcases
 * 
 * @param filePath is the path of testcases folder
 *
 * @return integer 0 in case testcase folder meets standards and requirements , also prints result of failures on screen
 *
 */
int checkFormatJudge (const char filePath[]){ // validation
	char temp[MAX_ARRAY_SIZE],strNumber[MAX_ARRAY_SIZE],buffer[MAX_ARRAY_SIZE];
	struct dirent *de;
	int numberOfInputs,numberOfOutputs,i;
	sprintf(temp, "%s/inputs", filePath);
	if(checkDir(filePath)==-1){
		changeColor(RED);
		printf("Input directory Does NOT exist ...\n");
		changeColor(WHITE);
		return -1;
	}
	sprintf(temp, "%s/outputs", filePath);
	if(checkDir(filePath)==-1){
		changeColor(RED);
		printf("Output directory Does NOT exist ...\n");
		changeColor(WHITE);
		return -1;
	}
	numberOfOutputs=numberOfFiles(temp);
	sprintf(temp, "%s/inputs", filePath);
	numberOfInputs=numberOfFiles(temp);
	if(numberOfInputs!=numberOfOutputs){
		changeColor(RED);
		printf("Error ...\n");
		printf("number of INPUTS does NOT match number of OUTPUTS.\n");
		changeColor(WHITE);
		return -1;
	}
	sprintf(temp, "%s/inputs", filePath);
	DIR *dr = opendir(temp);
	de = readdir(dr);// why these two things should exist ?!!
	de = readdir(dr);// :|
	for(i=0;i<numberOfInputs;i++){
		sprintf(temp, "input%d.txt", i+1);
		de = readdir(dr);
		if(strcmp(de->d_name,temp)!=0){
			changeColor(RED);
			printf("\nError , files don't match.\nyours : %s | must be : %s\n\n",de->d_name,temp);
			changeColor(WHITE);
			return -1;
		}
		sprintf(buffer, "%s/inputs/%s", filePath, temp);
		if(checkEmptyFile(buffer)!=1){
			changeColor(RED);
			printf("file %s does NOT exist or is Empty.\n",temp);
			changeColor(WHITE);
			return -1;
		}
	}
	closedir(dr);
	changeColor(GREEN);
	printf("\nInputs Correct ...\n");
	changeColor(WHITE);
	sprintf(temp, "%s/outputs", filePath);
	dr = opendir(temp);
	de = readdir(dr);// why these two things should exist ?!!
	de = readdir(dr);// :|
	for(i=0;i<numberOfInputs;i++){
		sprintf(temp, "output%d.txt", i+1);
		de = readdir(dr);
		if(strcmp(de->d_name,temp)!=0){
			changeColor(RED);
			printf("\nError , files don't match.\nyours : %s | must be : %s\n\n",de->d_name,temp);
			changeColor(WHITE);
			return -1;
		}
		sprintf(buffer, "%s/outputs/%s", filePath, temp);
		if(checkEmptyFile(buffer)!=1){
			changeColor(RED);
			printf("file %s does NOT exist or is Empty.\n",temp);
			changeColor(WHITE);
			return -1;
		}
	}
	closedir(dr);
	changeColor(GREEN);
	printf("Outputs Correct ...\n");
	changeColor(WHITE);
	return 0;
}

/** 
 * This function takes testcases folder and a code and judge testcases based on code given
 * 
 * @param filePath is the path of testcases folder
 * @param codePath is the path of code desired to be judged
 *
 * @return integer 1 in case everything goes smoothly ( and neccesserily does not mean that code itself is perfect )
 * and 0 in case of failure , the result of code is printed on screen
 *
 * ________________ RESULT OF JUDGING IS " NOT " RETURNED AS INTEGER _________________
 *
 */

int judge(const char filePath[],char codePath[]){
	int compileStatus=-1; // 0 for ok
	char exeDir[MAX_ARRAY_SIZE],cmd[MAX_ARRAY_SIZE],temp[MAX_ARRAY_SIZE],strNumber[4];
	char initialPath[MAX_ARRAY_SIZE];
	strcpy(initialPath,getcwd(temp, sizeof(temp)));
	int right=0, wrong=0, numberOfTestCases;
	sprintf(exeDir, "%s/a.exe", filePath);
	if ( checkFormatJudge(filePath)==0 ){ // 0 for ok
		pressAnyKey();
		getch();
		system("cls");
		if ( strlen(codePath)==0 ) {
			showPath();
			printf("Please input path for code needed to be judged ( including code itself )( 0 to exit ): ");
			scanf("%s",codePath);
			if(strcmp(codePath,"0")==0) return -1;
			fflush(stdin);
		}
		while(compileStatus!=0){
			compileStatus=compile(codePath,exeDir);
			if(compileStatus==0) break;
			getch();
			system("cls");
			showPath();
			printf("Please input path for code needed to be judged ( including code itself )( 0 to exit ): ");
			scanf("%s",codePath);
			fflush(stdin);
			if(strcmp(codePath,"0")==0) return -1;
			}
		system("cls");
		changeColor(GREEN);
		printf("Compiled succesfully.\n");
		changeColor(WHITE);
		pressAnyKey();
		getch();
		system("cls");
		int i;
		sprintf(temp, "%s/inputs", filePath);
		numberOfTestCases=numberOfFiles(temp);
		printf("number of test cases: %d\n\n",numberOfTestCases);
		chdir(filePath);
		for(i=0;i<numberOfTestCases;i++){
			sprintf(cmd, "a.exe <inputs/input%d.txt >tempfile.txt", i+1);
			system(cmd);
			sprintf(temp, "outputs/output%d.txt", i+1);
			//system("code.exe <in/1.txt >../testcases/outputs/1.txt"); // sample
			if(compareFiles(temp,"tempfile.txt")==0){
				changeColor(GREEN);
				printf("TestCase #%d : Right.\n",i+1);
				changeColor(WHITE);
				right++;
			}
			else{
				changeColor(RED);
				printf("TestCase #%d : Wrong.\n",i+1);
				changeColor(WHITE);
				wrong++;
			}
		}
		printf("_____________________________________");
		changeColor(GREEN);
		printf("\nCorrects : ");
		changeColor(WHITE);
		printf("%d",right);
		changeColor(RED);
		printf("\t\tIncorrect : ");
		changeColor(WHITE);
		printf("%d\n",wrong);
		int scale=100/numberOfTestCases;
		printf("Total Score : %d\n",scale*right);
		printf("_____________________________________\n");
		if (remove("a.exe") != 0) {
			changeColor(GREEN);
			printf("Unable to delete the exe file ...\n");
			changeColor(WHITE);
			getch();
		}
		if (remove("tempfile.txt") != 0) {
			changeColor(GREEN);
			printf("Unable to delete the exe file ...\n");
			changeColor(WHITE);
			getch();
		}
		pressAnyKey();
		getch();
		fflush(stdin);
		chdir(initialPath);
		return 0;
	}
	else {
		changeColor(RED);
		printf("There is a problem with testcase folder.\n");
		changeColor(WHITE);
		pressAnyKey();
		getch();
		return -1;
	}
}
