#include "generator.h"

extern char input[], exeFile[];

/**
* function to check if an unique file exist or not
*
* @param name of the file that function check to see if exist
* @return integer 1 if exist, 0 if not
*/
int doesExist(const char* name) {
	FILE* f;
	if (f = fopen(name, "r")) {
		fclose(f);
		return 1;
	}
	return 0;
}

/**
* function to generate correct outputs using existing correct input files
*
* @return integer as number of testcases
*/
int generatorFromFile() {
	puts("<< DESCRIPTION >>"
		"\nPut all of your input files in folder \"in\", and name them using name format below:"
		"\ninput[input_number].txt\n"
		"\nAfter you did steps above,");
	
	system("pause");
	system("cls");
	getchar(); // emptying buffer (extra \n in buffer)
	
	char inputPath[MAX_PATH_SIZE];
	int counter = 1;
	while (1) {
		sprintf(inputPath, ".\\in\\input%d.txt", counter);
		// checking input file
		if (!doesExist(inputPath))
			break;
		// making output based on input file
		char outputPath[MAX_PATH_SIZE];
		sprintf(outputPath, ".\\out\\output%d.txt", counter);
		char command[MAX_COMMAND_SIZE];
		sprintf(command, "%s<%s>%s", exeFile, inputPath, outputPath);
		system(command);

		counter++;
	};
	return counter;
}

/**
* function to generate correct outputs using correct inputs that are entered in cmd shell
*
* @return integer as number of testcases
*/
int generatorFromCMD() {
	int counter = 1;
	puts("<< DESCRIPTION >>"
		"\nEnter each line of any input in one line."
		"\nEnter \"EOT\" at the end of each testcase."
		"\nEnter \"END\" to stop."
		"\n---");

	while (1) {
		gets(input);
		
		if (!strcmp(input, "END"))
			break;
		
		//saving inputs
		FILE* in;
		char inputPath[MAX_PATH_SIZE];
		sprintf(inputPath, ".\\in\\input%d.txt", counter);
		in = fopen(inputPath, "w");
		
		while (strcmp(input, "EOT")) {
			fputs(input, in);
			fputs("\n", in);
			gets(input);
		}
		// End of each test case
		puts("---");
		fclose(in);
		//saving outputs
		char outputPath[MAX_PATH_SIZE];
		sprintf(outputPath, ".\\out\\output%d.txt", counter);
		char command[MAX_COMMAND_SIZE];
		sprintf(command, "%s<%s>%s", exeFile, inputPath, outputPath);
		system(command);
		
		counter++;
	}
	system("cls");
	return counter;
}

/**
* function to control above functions for making testcases
*
* @return integer as number of testcases
*/
int generator() {
	puts("How do you want me to get inputs?"
	"\n--------------------------------"
	"\n1 : Get inputs one by one in here"
	"\n2 : Get inputs from existing files\n"
	"\n>>> Enter your choice:");
	
	int choice;
	scanf("%d", &choice);
	while(choice != 1 && choice != 2)
		scanf("%d", &choice);
	system("cls");
	
	system("if not exist \"in\" mkdir in");
	system("if not exist \"out\" mkdir out");

	if (choice == 2)
		return generatorFromFile();
	else
		return generatorFromCMD();
}
