#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "globalHeader.h"


/**
 * @help
 * handels help!
 * no argument needed
 * 
 * 
 */

void help() /*shoud be updated last*/
{
	putchar('\n');
	printf("  \n%s  %s\n\n", GRN "FORMAT:" RESET, "adjudicator -s -h " MAG "-G " CYN "IOFolder" RESET " " MAG "-J" RESET " " CYN "program.c" RESET); //temp names
	printf("  \n%s\n         %s\n\n", RED "NOTICE:  " RESET "Options " MAG "-G" RESET " and " MAG "-J" RESET " cannot be active simultaneously.But one of them must be active.",
		   "In each terminal session " MAG "Generator" RESET " module should be run at least once before using " MAG "Judge" RESET " module.");
	printf("  \n%s\n\n", GRN "TESTCASE_FOLDER_STRUCTURE:" RESET);
	printf("        " CYN "TestCase" RESET "\n"
		   "          /  \\\n"
		   "         /    \\\n"
		   "        /      \\\n"
		   "       /        \\\n"
		   "    " CYN "Input     Output" RESET "\n"
		   "      |          |\n"
		   "    1.in       1.out\n"
		   "    2.in       2.out\n"
		   "    3.in       3.out\n"
		   "    ...\t       ...\t\t\n"
		   "    x.in       y.out\n\n"
		   "");
	printf("  \n%s\n\n", GRN "OPTIONS:" RESET);
	printf("  %-15s%20s\n\n", "-G", "Sets program to " MAG "Generator" RESET " mode");
	printf("      %-20s\n", "--This option requiers an argument of input directory in the format specified above.");
	printf("      %-20s\n\n", "--In this mode " CYN "program.c" RESET " is judgeFile.c");
	printf("  %-15s%20s\n\n", "-J", "Sets program to " MAG "Judge" RESET " mode");
	printf("      %-20s\n\n", "--In this mode " CYN "program.c" RESET " is suspectFile.c");
	printf("  %-15s%20s\n\n", "-h", "Show all available options.");
	printf("  \n%s\n", RED "NOTICE:  " RESET "All given arguments must be name of a file exsisting in the current directory or it's path.");
}

int main(int argc, char *argv[])
{

	int opt, necessaryOptionCount = 0;
	while ((opt = getopt(argc, argv, ":G:Jhs")) != -1)
	{

		switch (opt)
		{
		case 'G': //turn on
			necessaryOptionCount++;
			generatorModuleState = ON;
			strcpy(inOutFileAdress, optarg);
			system("rm -rf /usr/local/adjudicator/temp 2> /dev/null");
			system("mkdir /usr/local/adjudicator/temp 2> /dev/null");
			system("rm -rf TestCase");
			system("mkdir TestCase");
			system("mkdir TestCase/Input");
			system("mkdir TestCase/Output");
			break;

		case 'J': //turn on judge module
			necessaryOptionCount++;
			judgeModuleState = ON;
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

		if (necessaryOptionCount > 1)
		{ // catch dual operation mode
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  More than one operation modes were selected.\n          For more info enter adjudicator -h.");
			return 6;
		}
	}

	if (necessaryOptionCount == 0)
	{ // catch lack of operation mode
		printf("  \n%s\n\n", YEL "WARNING:" RESET "  Operation mode was not specified.\n          For more info enter adjudicator -h.");
		return 8;
	}

	if (argc - optind < 1)
	{ //catch lack of main argument
		printf("  \n%s\n\n", YEL "WARNING:" RESET "  program.c argument was not provided.\n          For more info enter adjudicator -h.");
		return 7;
	}
	// optind is for the extra arguments
	// which are not parsed
	for (; optind < argc; optind++)
	{
		if (argc - optind > 1)
		{ //catch extra argument
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Extra arguments were given.\n          For more info enter adjudicator -h.");
			return 5;
		}

		//printf("\t\t\n\nextra arguments %s %d argc: %d:\n", argv[optind],optind,argc);
	}

	if (generatorModuleState == ON)
	{

		strcpy(judgeFileAdress, argv[argc - 1]);
		char ioAdressHold[ADRESS_ARRAY_SIZE];
		strcpy(ioAdressHold, inOutFileAdress);
		if (dirExist(ioAdressHold) == YES)

		{ //catch given directory not existing

			char argument[2 * ADRESS_ARRAY_SIZE]; // hold variable system argments
			strcpy(argument, "rsync -r ");		  //copy content of folder to localy created folder
			strcat(argument, inOutFileAdress);
			//rsync needs / at the end of first argument to execute properly
			//there might be some problems regarding the fact that people maight
			//put / at end of argument
			//The next piece handels this issue
			if (argument[strlen(argument) - 1] != '/')
				strcat(argument, "/");
			strcat(argument, " TestCase/Input");
			system(argument);
			strcpy(inOutFileAdress, "TestCase/Input");
			system(argument);
		}

		else
		{
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Sepecified directory dose not exist.\n          For more info enter adjudicator -h.");
			return 9;
		}

		char judgeAdressHold[ADRESS_ARRAY_SIZE] = " ";
		strcpy(judgeAdressHold, judgeFileAdress);
		if (typeCExist(judgeAdressHold) == YES)
		{ //catch given file not being .c file

			if (generator(judgeAdressHold) == NO)
			{
				printf("  \n%s\n\n", YEL "WARNING:" RESET "  Generation proccess failed\n          For more info enter adjudicator -h.");
				return 10;
			}
			else
				return 0;
		}
		else
		{
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Sepecified judgeFile.c file dose not exist.\n          For more info enter adjudicator -h.");
			return 11;
		}
	}

	if (judgeModuleState == ON)
	{
		strcpy(inOutFileAdress, "TestCase/Input");
		strcpy(suspectFileAdress, argv[argc - 1]);
		char suspectAdressHold[ADRESS_ARRAY_SIZE];
		char ioAdressHold[ADRESS_ARRAY_SIZE];
		strcpy(ioAdressHold, inOutFileAdress);
		strcpy(suspectAdressHold, suspectFileAdress);
		if (dirExist(ioAdressHold) == YES)
		{

			if ((inFileCounter("TestCase/Input", ".in") == -1) || (inFileCounter("TestCase/Output", ".out") == -1))
			{
				printf("  \n%s\n\n", YEL "WARNING:" RESET "  generation process has malfunctioned,\n          Or one of the IO folders has been croupted.\n          You can try running " MAG "Generator" RESET " module again");
				return 12;
			}

			else if (inFileCounter("TestCase/Input", ".in") != inFileCounter("TestCase/Output", ".out"))
			{
				printf("  \n%s\n\n", YEL "WARNING:" RESET "  generation process has malfunctioned,\n          Input count and output count dont match.\n          You can try running " MAG "Generator" RESET " module again");
			}
		}
		else
		{
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Sepecified directory dose not exist.\n          For more info enter adjudicator -h.");
			return 13;
		}

		if (typeCExist(suspectAdressHold) == YES)
		{
			judge(suspectAdressHold, inFileCounter("TestCase/Input", ".in"));
		}

		else
		{
			printf("  \n%s\n\n", YEL "WARNING:" RESET "  Sepecified suspectFile.c file dose not exist\n          Or it is not a .c file\n          For more info enter adjudicator -h.");
			return 14;
		}
	}


	return 0;
}
