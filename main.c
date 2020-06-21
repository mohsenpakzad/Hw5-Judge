#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "generatorHeader.h"

//Global var
//move to header

/**
 * @help
 * handels help!
 * no argument needed
 * fucntion suold be cross-platrofrm - not tested
 * 
 * a -j option will be added so if you have already generated your outputs (wich shoud be in the specifed format or generated bay the program before)
 * also unistall would be nice
 * 
 * */

void help()
{
	putchar('\n');
	printf("  \n%s  %s\n\n", GRN "FORMAT:" RESET, "adjudicator -s -h -l logfile "MAG"-G -l"RESET" IN/OUT SUSPECT"); //temp names
	printf("  \n%s\n         %s\n\n", RED "NOTICE:  " RESET "Options "MAG"-G"RESET" and "MAG"-J"RESET" cannot be active simultaneously.But one of them must be present.",
	"Also in each terminal session "MAG"Generator"RESET" module should be run at least once before using "MAG"Judge"RESET" module.");
	printf("  \n%s\n\n", GRN "OPTIONS:" RESET);													 //temp names
	printf("  %-15s%20s\n\n", "-G", "Sets program to "MAG"Generator"RESET" mode");
	printf("  %-15s%20s\n\n", "-J", "Sets program to "MAG"Judge"RESET" mode");
	printf("  %-15s%20s\n\n", "-s", "Show result of all test cases on screen.");
	printf("  %-15s%20s\n\n", "-h", "Show all available options.");
	printf("  %-15s%20s\n\n", "-l", "Specify a file to direct output.");
	printf("      %-20s\n\n", "--This option requiers an argument in the format specified above.");
	printf("  \n%s\n", RED "NOTICE:  " RESET "All given arguments must be name of a file exsisting in the current directory or it's path.");
}

//Global var
//arg c argv https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
int main(int argc, char *argv[])
{

	int opt,necessaryOptionCount = 0;
	//create a file so that we can check if generator module has been ran at least once
	system("cd /tmp");
	system("touch generatorModule.History");
	sytem("echo \"0\" > generatorModule.History");//put zero for no
	system("trap 'rm -f /tmp/generatorModule.History; exit' ERR EXIT"); // delete file if terminal is closed due to error or manual exit

	while ((opt = getopt(argc, argv, ":l:GJhs")) != -1)
	{

		
		switch (opt)
		{
		case 'G': //turn on 
			necessaryOptionCount++;
			generatorModuleState = ON;
			system("bash generatorModuleOn.sh");
			break;

		case 'J': //turn on judge module
			necessaryOptionCount++;
			judgeModuleState = ON;
			break;
		
		case 's': //show testCase results
			testCaseViewState = 1;
			break;
		case 'L': //set a custom file for log results
			strcpy(logAddress, optarg);
			break;
		case 'h': //help
			help();
			return 1;
			break;
		case ':': //catch lack of option argument
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  One of invoked options requiers an argument.\n          For more info enter adjudicator -h.");
			return 2;
			break;
		case '?': //catch unknown argument
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Invalid options.\n          For more info enter adjudicator -h.");
			return 3;
			break;
		}

		if(necessaryOptionCount > 1){// catch dual operation mode
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  More than one operation modes were selected.\n          For more info enter adjudicator -h.");
			return 6;
		}
	}
	
	if(necessaryOptionCount == 0){ // catch lack of operation mode
		printf("  \n%s\n\n", YEL "WARNING:" RESET "  Operation mode was not specified.\n          For more info enter adjudicator -h.");
	}

	if (argc - optind < 2)
	{ //catch lack of main argument

		printf("  \n%s\n\n", YEL "WARNING:" RESET "  Sufficent main arguments were not provided.\n          For more info enter adjudicator -h.");
	}
	// optind is for the extra arguments
	// which are not parsed
	for (; optind < argc; optind++)
	{	
		if (argc - optind > 2)
		{ //catch extra argument
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Extra arguments were given.\n          For more info enter adjudicator -h.");
			return 5;
		}

		

		//printf("\t\t\n\nextra arguments %s %d argc: %d:\n", argv[optind],optind,argc);
	}
	strcpy(inOutFileAdress,argv[argc -2]);
	strcpy(judgeFileAdress,argv[argc -1]);

	//catch 
	
	return 0;
}
