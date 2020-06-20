#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "generator.h"
//#ifdef __WIN32__
//#include <unistd.h>
//#endif //__WIN32__




//Global var
//move to header

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


char logAddress[240];
char judgeFile[240];
//char 
/**
 * @help
 * handels help!
 * no argument needed
 * fucntion suold be cross-platrofrm - not tested
 * 
 * im thinking about adding a KING functionality
 * so that you can set an static judge file for your current terminal session
 * 
 * also unistall would be nice
 * 
 * */

void help(){
	putchar('\n');
	printf("  \n%s  %s\n\n",GRN"FORMAT:"RESET,"adjudicator -s -h -L logfile JUDGE SUSPECT"); //temp names 
	printf("  \n%s\n\n",GRN"OPTIONS:"RESET); //temp names 
	printf("  %-15s%20s\n\n","-s","Show result of all test cases on screen");
	printf("  %-15s%20s\n\n","-h","Show all available functionality");
	printf("  %-15s%20s\n\n","-L","Specify a certain file to write results in");
	printf("      %-20s\n\n","--This option requiers an argument in the format specified above.");
	printf("  \n%s\n",RED"NOTICE:  "RESET"All given arguments must be name of a file exsisting in the current directory or it's absolute path");
}

//Global var

int main(int argc,char *argv[]) {
#ifdef __linux__

 
#include <unistd.h> 

		int opt;
		
		
		while ((opt = getopt(argc, argv, ":L:hs")) != -1)
		{
			switch (opt)
			{
			case 's': //show testCase results
				printf("OK\n"); //temp
				break;
			case 'L': //set a custom file for log results
				strcpy(logAddress,optarg);
				printf("Log File is: %s\n",logAddress);
				break;
			case 'h': //help
				help();
				return 1;
				break;
			case ':': //catch lack of option argument
				printf("  \n%s\n\n",YEL"WARNING:"RESET"  One of invoked options requiers an argument.\n          For more info enter adjudicator -h.");
				return 2;
				break;
			case '?' : //catch unknown argument
				printf("  \n%s\n\n",YEL"WARNING:"RESET"  Invalid options.\n          For more info enter adjudicator -h.");
				return 3;
				break;
			}
		}
		//printf("argc: %d\toptind: %d\n",argc,optind);  temp
		if (argc - optind < 2){//catch lack of main argument

			printf("  \n%s\n\n",YEL"WARNING:"RESET"  Sufficent main arguments were not provided.\n          For more info enter adjudicator -h.");

		}
		// optind is for the extra arguments 
		// which are not parsed 
		for (; optind < argc; optind++) {
			if(optind > 3){//catch extra argument
				printf("  \n%s\n\n",YEL"WARNING:"RESET"  Extra arguments were given.\n          For more info enter adjudicator -h.");
				return 5;
			
			}
	
			
			//printf("\t\t\n\nextra arguments %s:\n", argv[optind]);
		}

		

		return 0;
	

#endif // __linux__
    
}
