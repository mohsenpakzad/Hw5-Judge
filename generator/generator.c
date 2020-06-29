#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generator.h"

char input[10000000000], exefile[1000];

int doesExist(const char *name){
	FILE *f;
	if((f = fopen(name, "r"))){
		fclose(f);
        return 1;
	}
	return 0;
}

void testCases(){
	int counter = 1;
	printf("DESCRIPTION :\ninput your inputs\nthen when your inputs for each test case finished input \"EOT\"\nat the end input \"END\" to stop.\n******\n");
	system("mkdir in");
	system("mkdir out");
	while(1){
		gets(input);
		if(strcmp(input, "END") == 0)
			break;
		else{
			//saving inputs
			FILE *in;
			char inp[100] = ".\\in\\input0.txt";
			inp[10] = counter + '0';
			in = fopen(inp, "w");
			while(strcmp(input, "EOT") != 0){
				fputs(input, in);
				fputs("\n", in);
				gets(input);
			}
			// End of each test case
			printf("-------\n");
			fclose(in);
			//saving outputs
			char out[100] = ".\\out\\output0.txt";
			out[12] = counter + '0';
			char command[100];
			strcpy(command, exefile);
			strcat(command, "<");
			strcat(command, inp);
			strcat(command, ">");
			strcat(command, out);
			system(command);
			counter++;	
		}
	}
}
