#include "judge.h"

#define MAX_NAME_SIZE 1000 + 1
#define MAX_ADDRRESS_SIZE 10000 + 1


/**
* this function campare the contains of the files .
*
* @param FILE * firstPtr : the first file to campare,
* @param FILE * secondPtr : the second file to campare,
* @return integer as result of comparing two files contain . if they are equal result is 0 otherwise is -1 ;).
*/
int compareFile(FILE * firstPtr, FILE * secondPtr){
    char firstChar, secondChar;

    do{
        firstChar = fgetc(firstPtr);
        secondChar = fgetc(secondPtr);
        if (firstChar != secondChar)
            return -1;
    }while (firstChar != EOF && secondChar != EOF);

    if (firstChar == EOF && secondChar == EOF)
        return 0;
    else
        return -1;
}

/**
* this function do judging proccess  .
*
* @param :Nothing,
* @return :Nothing;).
*/
void judgeProcces(){
    system("color 09");

    char dirCommand[MAX_NAME_SIZE] ;

	//if there is already a dir in this address it gives us an error. 
    sprintf(dirCommand, "cd /d %s && rmdir /q /s %s%s", fileAddress, codeName, "out");
    system(dirCommand);
    
    system("cls");
    
    sprintf(dirCommand, "cd /d %s && mkdir %s%s", fileAddress, codeName, "out");
    system(dirCommand);

    double right = 0;
    double wrong = 0;
    double total = 0;
    double timeL = 0;
    double tolalTime = 0;

    for(int index=1;;index++){
        total = index;
        FILE *in;
        FILE *out1;
        FILE *out2;
        char addressCommand[MAX_ADDRRESS_SIZE];
        char name[MAX_NAME_SIZE];
        char name2[MAX_NAME_SIZE];
        char name3[MAX_NAME_SIZE];

        sprintf(name, "%s.\\%s\\in\\input%d.txt", fileAddress, fileName, index);
        in = fopen(name, "r");
        if (in == NULL)
            break;

        sprintf(name3,"%s.\\%s\\out\\output%d.txt",fileAddress,fileName,index);
        sprintf(name2,"%s.\\%s%s\\output%d.txt",fileAddress,codeName,"out",index);
        sprintf(addressCommand, "%s.\\%s.exe < %s >> %s", codeAddress, codeName, name, name2);

        time_t begin = time(NULL);
        system(addressCommand);
        time_t end = time(NULL);
        tolalTime += end - begin;

        out1 = fopen(name2,"r");
        out2 = fopen(name3,"r");
        if((end - begin)>timeLimit){
            printf("tastcase %d : timelimitexceeded! :O \n",index);
            timeL++;
        }

        else {
            if (compareFile(out1, out2) == 0) {
                printf("tastcase %d : correct. :) \n", index);
                right++;
            }
            
            else {
                printf("tastcase %d : wrong answer. :( \n", index);
                wrong++;
            }
        }

        fclose(out1);
        fclose(out2);
    }

    printf("total time is %.0lf seconds\n", tolalTime);
    printf("total time is %d seconds\n", timeLimit);
    printf("tastcase right : %.0lf\n",right);
    printf("tastcase wrong : %.0lf\n",wrong);
    printf("tastcase timelimit : %.0lf\n",timeL);
    printf("tastcase total : %.0lf\n",total-1);
    printf("score : %.0lf\n",(right/(total-1))*100);
    printf("Good Luck ;) \n");
    printf("__________________________<AHM>____________________________\n\n");

    system("pause");

}
