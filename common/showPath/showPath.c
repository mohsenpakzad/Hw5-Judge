#include "showPath.h"

/** 
 * This function shows the path we are in right now
 */

void showPath(){
	char cwd[100];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	    printf("Current working dir: %s\n", cwd);
	}
	else {
		changeColor(RED);
	    perror("Unable to show path ...");
	    changeColor(WHITE);
	}
}
