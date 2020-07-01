#include "changeColor.h"

/** 
 * This function gets a color's MACRO defiened in mainGlobal.h and turns output color into it
 * 
 * @param color should be a color MACRO defiened in mainGlobal.h
 *
 * @return integer 1 in case of success and -1 in opposite case
 *
 */

int changeColor (char color[]){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (strcmp(color,"green")==0||strcmp(color,"g")==0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN );
		return 1;
	}
	else if (strcmp(color,"red")==0||strcmp(color,"r")==0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED );
		return 1;
	}
	else if (strcmp(color,"white")==0||strcmp(color,"w")==0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		return 1;
	}
	else {
		return -1;
	}
}
