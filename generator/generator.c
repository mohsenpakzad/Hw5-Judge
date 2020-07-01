#include "generator.h"

#define fullAddress 2

/**
* this function do generate procces : generate output file related to each input file
 * and make directory that contains output files near the input directory .
*
* @param :Nothing,
* @return :Nothing;).
*/
void generateProcces() {
    int max=0;
    char fname[100] ;

    sprintf(fname,"cd /d %s.\\%s&& rmdir /q /s out",fileAddress,fileName);
    system(fname);
    system("cls");
    sprintf(fname,"cd /d %s.\\%s&& mkdir out",fileAddress,fileName);
    system(fname);

    double totaltime =0;

    for (int i = 1;; i++) {
        FILE *in;
        char str[100000] ;
        char name[1000];
        char name2[1000];

        sprintf(name,"%s.\\%s\\in\\input%d.txt",fileAddress,fileName,i);

        in = fopen(name, "r");
        if (in == NULL)
            break;

        sprintf(name2,"%s.\\%s\\out\\output%d.txt",fileAddress,fileName,i);
        sprintf(str,"%s.\\%s.exe < %s >> %s",codeAddress,codeName,name,name2);

	time_t begin = time(NULL);
        system(str);
	time_t end = time(NULL);
        if((end-begin)>max) max=end-begin;
        totaltime += end-begin;

    }

    system("cls");
    system("color 0A");

    printf("max time is %d seconds\n", max);
    printf("total time is %.0lf seconds\n", totaltime);

    puts("make output!");
    system("pause");
}


/**
* this function do generate procces : generate output file related to each input file
 * and make directory that contains output files near the input directory .
*
* @param aon : ,
* @return :Nothing;).
*/
void maketastcase(int addressType){
    system("cls");
    system("color 09");

    int testCaseNum;

    if(addressType == fullAddress ){
        printf("puts address : ");
        scanf(" %s",fileAddress);
    }

    printf("name you want : ");
    scanf(" %s",fileName);
    printf("number of test case : ");
    scanf("%d",&testCaseNum);

    char fname[1000];

    sprintf(fname,"cd /d %s&&rmdir /q /s %s",fileAddress,fileName);
    system(fname);
    system("cls");
    sprintf(fname,"cd /d %s&&mkdir %s",fileAddress,fileName);
    system(fname);
    sprintf(fname,"cd /d %s.\\%s&&mkdir in",fileAddress,fileName);
    system(fname);

    for(int i = 1;i<=testCaseNum;i++){
        sprintf(fname,"echo.>%s.\\%s\\in\\input%d.txt",fileAddress,fileName,i);
        system(fname);
        system("color 0B");
        puts("save it!");
        system("pause");
        sprintf(fname,"%s.\\%s\\in\\input%d.txt",fileAddress,fileName,i);
        system(fname);
    }

    system("color 0A");
    puts("done!");
    system("pause");
}
