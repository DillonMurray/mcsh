#include "define.h"

#define MAX_VARIABLES   100
#define MAX_ALIASES     100

char  buffer [512];
char* commands [3];
int   commandCount = 0;
char* directory = NULL;
FILE* fp;
FILE* fpI;

int       variableCount;
int       aliasCount;
variable* userVariables [MAX_VARIABLES];
alias*    userAliases [MAX_ALIASES];
variable* vHead;
alias*    aHead;
variable* vCur;
alias*    aCur;
