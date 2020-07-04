#include "checkEmptyFile.h"

/** 
 * This function takes a file(path) and checks if it's empty or not
 * 
 * @param filePath is the path of file needed to be checked
 *
 * @return integer 0 in case of being empty , 1 in case being filled and -1 in case of error
 *
 */

int checkEmptyFile(const char filePath[]){
	FILE *fp;
	fp = fopen(filePath,"r");
	int size;
	if (NULL != fp) {
	    fseek (fp, 0, SEEK_END);
	    size = ftell(fp);
	
	    if (0 == size) {
//	        printf("file is empty\n");
	        fclose(fp);
	        return 0;
	    }
	    else {
	    	fclose(fp);
	    	return 1;
		}
	}
	else{
//		printf("File %s does NOT exist.\n");
		return -1;
	}
}
