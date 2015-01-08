#ifndef COMMANDS_H
#define COMMANDS_H
#include "define.h"

/************************************

commands.h
- contains prototypes for parsing functions checking legitimacy of commands
- last modified: Apr 14, 2013

************************************/

/*** processes mcshCommands() and, based on return value, declares if command failed ***/
void checkCommand ();

/*** Clears commands[], buffer, and command count in preparation for next parse ***/
void clearCommand ();

/*** Parses user/file input, inserts @var reference, then calls checkCommand() ***/
void getCommand ();

/*** Switch for checking initial input, then calls appropriate function
     Returns 1 on matched command, 0 for no match, and exits on command exit ***/
int  mcshCommands ();

/*** Checks if first input is an alias, if so inserts alias value
     Returns 1 on alias match, 0 for no match ***/
int  checkAlias ();

/*** Prints echo ***/
void mcshEcho ();

void mcshWhere ();

#endif
