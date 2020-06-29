#include "compile.h"

/** 
 * This function takes a .c code path ( including name of the code ) and tries to compile it
 * 
 * @param filePath is path of code ( name of the code must be included )
 * @param exeName is desiered name of the output file
 *
 * @return integer 0 in cases of success
 *
 */

int compile(const char filePath[] ,char exeName[]){
	struct stat buffer;
	int stat=-1; // 0 for ok
	char cmd[50]="gcc -o ";
	strcat(cmd,exeName);
	strcat(cmd," ");
	strcat(cmd,filePath);
//	puts(cmd);
	stat=system(cmd);
	if(stat==0){
		return 0;
	}
	else return -1;
}
