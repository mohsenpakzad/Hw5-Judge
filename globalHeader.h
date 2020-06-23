#define ADRESS_ARRAY_SIZE 512
//string color
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//module on/off
#define ON 1
#define OFF 0
//fucntion answer
#define YES 1
#define NO 0
//input adress
char logAddress[ADRESS_ARRAY_SIZE];
char judgeFileAdress[ADRESS_ARRAY_SIZE];
char inOutFileAdress[ADRESS_ARRAY_SIZE];
char suspectFileAdress[ADRESS_ARRAY_SIZE];


//module state
int judgeModuleState;
int generatorModuleState;
int testCaseViewState;

//function
int dirExist(const char fileAdress[ADRESS_ARRAY_SIZE]);
int typeCExist(const char fileAdress[ADRESS_ARRAY_SIZE]); 
int compile(char fileAdress[ADRESS_ARRAY_SIZE]); //notDone
int ioFileCounter(const char fileAdress[ADRESS_ARRAY_SIZE]);

