#ifndef INIT_H
#define INIT_H
#include "define.h"

/************************************

init.h
- contains prototypes for initialization functions
- also retrieves and processes mcsh resource file
- last modified: Apr 14, 2013

************************************/

/*** initializes global data, initializes HOME variable, opens mcshrc and calls fGet(), then attempts to open argv[1] ***/
void mcshInit (char* argv []);

/*** MCSH and startup info- no necessary function ***/
void mcshStart ();

/*** Input prompt repeated during interactive mode ***/
void mcshPrompt ();

/*** Almost identical to getCommand(), but altered for the purpose of mcshrc
     Returns 1 on successful parse, -1 on exit mcshrc ***/
int  fGet ();

/*** Almost identical to mcshCommands(), altered for the purpose of mcshrc
     Returns 1 on successful command, 0 on failed command, and -1 on exit mcshrc ***/
int  fCommands ();

#endif
