#include "generator/generator.h"
#include "judge/judge.h"
#include "mainGlobal.h"
#include "main.h"

int main(int argc, char *argv[]) {
	char folderPath[100];
	char codePath[100];
	int choice;
	system("cls");
	if(argc==1){
		do{
			choice=menuSelect();
			switch(choice){
				case 1 : system("cls");
							showPath();
							printf("Please input folder path ( must include validation code and folder containing inputs ): ");
							gets(folderPath);
							generator(folderPath);
							break;
				case 2 : system("cls");
							showPath();
							printf("Please input folder path ( must include folder containing inputs and outputs ): ");
							gets(folderPath);
							judge(folderPath,codePath);
							strcpy(codePath,"");
							break;
				case 0 : exit(0);
			}
			system("cls");
		}while(1);
	}
	else{
	/*
		0 - unknown
		1 - for generator : -g path
		2 - for judge : -j testcase path
		3 - for judge : -j testcase path -c code path
	*/
		choice=parser(argc,argv);
		switch(choice){
			case 0 :changeColor(RED);
					printf("The syntax is Incorrect.\n");
					changeColor(WHITE);
					break;
			case 1 :generator(argv[2]);
					break;
			case 2 :judge(argv[2],codePath);
					break;
			case 3 :judge(argv[2],argv[4]);
					break;
		}
	}
	return 0;
}
