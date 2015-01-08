#ifndef DEFINE_H
#define DEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//#include <pwd.h>

/************************************

define.h
- contains global data and defines
- last modified: Apr 12, 2013

************************************/

#define MAX_VARIABLES   100
#define MAX_ALIASES     100
typedef unsigned int size_t;

extern char  buffer [512];
extern char* commands [3];
extern int   commandCount;
extern char* directory;
extern FILE* fp;
extern FILE* fpI;

typedef struct variable variable;
typedef struct alias alias;

struct variable
{
    variable* next;
    variable* prev;
    char* name;
    char* value;
};

struct alias
{
    alias* next;
    alias* prev;
    char* name;
    char* value;
};

extern int       variableCount;
extern int       aliasCount;
extern variable* userVariables [MAX_VARIABLES];
extern alias*    userAliases [MAX_ALIASES];
extern variable* vHead;
extern alias*    aHead;
extern variable* vCur;
extern alias*    aCur;

#endif




