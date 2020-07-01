#include "searchInFile.h"

/** 
 * This function checks if a string exists in file or not
 * 
 * @param filePath is the path of the file
 * @param str is the string we want to search in file
 *
 * @return integer 1 if any was found and 0 otherwise
 *
 */

int searchInFile(char *filePath, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	if((fp = fopen(filePath, "r")) == NULL) {
		return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
//			printf("A match found on line: %d\n", line_num);
//			printf("\n%s\n", temp);
			find_result++;
			return 1;
		}
		line_num++;
	}

	if(find_result == 0) {
//		printf("\nCouldn't find a match.\n");
	}
	
	if(fp) {
		fclose(fp);
	}
   	return(0);
}
