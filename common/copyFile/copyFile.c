#include "copyFile.h"

/** 
 * This function copies content of second file into first file
 * 
 * @param pathOfFirstFile is the path of first file
 * @param pathOfSecondFile is the path of second file
 *
 * @return integer 0 in case of success
 *
 */

int copyFile(const char pathOfFirstFile[] ,const char pathOfSecondFile[]){
	FILE *fptr1, *fptr2; 
    char filename[MAX_ARRAY_SIZE], c; 
    
    fptr1 = fopen(pathOfSecondFile, "r");
    if (fptr1 == NULL){ 
    	changeColor(RED);
        printf("Cannot open file : %s \n", pathOfSecondFile);
        changeColor(WHITE);
        return -1;
    }
    
    fptr2 = fopen(pathOfFirstFile, "w");
    if (fptr2 == NULL) { 
    	changeColor(RED);
        printf("Cannot open file : %s \n", pathOfFirstFile);
        changeColor(WHITE);
        return -1;
    } 
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    }
    fclose(fptr1); 
    fclose(fptr2); 
    return 0; 
}
