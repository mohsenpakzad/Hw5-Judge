#include "common.h"

int menuSelect(){
	printf("\n\n\t\t\t   ___           _                             _                 \n");
	printf("\t\t\t  |_  |         | |                           | |                \n");
	printf("\t\t\t    | |_   _  __| | __ _  ___    ___ _   _ ___| |_ ___ _ __ ___  \n");
	printf("\t\t\t    | | | | |/ _` |/ _` |/ _ \\  / __| | | / __| __/ _ \\ '_ ` _ \\ \n");
	printf("\t\t\t/\\__/ / |_| | (_| | (_| |  __/  \\__ \\ |_| \\__ \\ ||  __/ | | | | |\n");
	printf("\t\t\t\\____/ \\__,_|\\__,_|\\__, |\\___|  |___/\\__, |___/\\__\\___|_| |_| |_|\n");
	printf("\t\t\t                    __/ |             __/ |                      \n");
	printf("\t\t\t                   |___/             |___/                       \n\n\n\n");
	printf("\t			1 - make testcases ( input file and code needed )\n");
	printf("\t			2 - judge ( testcase file and a code needed )\n");
	printf("\t			0 - quit\n\n");
	int c;
	char s[3];
	do{
		printf("\t			please enter your choice (0-2): ");
		gets(s);
	c=atoi(s);
	}while(c<0 || c>2);
	return c;
}

int compile(char *filePath,char *exeName){
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

void showPath(){
	char cwd[50];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	    printf("Current working dir: %s\n", cwd);
	}
	else {
	    perror("getcwd() error");
	}
}

int numberOfFiles(const char * filePath){
	struct dirent *de;  // Pointer for directory entry 
	int fileCounter=0; 
    DIR *dr = opendir(filePath); 
    if (dr == NULL){  // opendir returns NULL if couldn't open directory
        printf("Could not open current directory.\n" ); 
        return 0; 
    } 
    while ((de = readdir(dr)) != NULL){
//    	printf("%s\n", de->d_name);
        fileCounter++;
	}
    closedir(dr);
    return fileCounter-2; 
}

int checkEmptyFile(const char *filePath){
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

void pressAnyKey(){
	puts("\nPress any key to continue...");
}

int checkDir(const char * dirPath){
	DIR* dir = opendir(dirPath);
	if (dir) {
	    closedir(dir);
	    return 1;
	}
	else {
	    return -1;
	}
}
