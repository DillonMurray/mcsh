#ifndef LEXICO_H
#define LEXICO_H

/************************************

lexico.h
- contains prototypes for sorting, updating, removing, and traversing variables and aliases
- last modified: Apr 14, 2013

************************************/

/*** Set (av)Cur to (av)Head ***/
void mcshHead   (char type []);

/*** Searches aliases/variables for passed name and sets (av)Cur if found and returns 1 -
     Sets (av)Cur to NULL on failure and returns 0 ***/
int  mcshFind   (char type [], char name []);

/*** Adds new variable/alias ***/
void mcshInsert (char type [], char name [], char value []);

/*** Sets (av)Cur to next alias or variable ***/
void mcshNext   (char type []);

/*** Removes alias/variable ***/
void mcshRemove (char type [], char name []);

/*** Sorts aliases and variables alphabetically ***/
void mcshSort   ();

/*** Updates value of passed alias or variable ***/
void mcshUpdate (char type [], char name [], char value []);

#endif
