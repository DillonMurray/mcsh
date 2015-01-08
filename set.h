#ifndef SET_H
#define SET_H
/************************************

set.h
- contains variable and set related protoypes
- often calls lexico.h functions
- last modified: Apr 14, 2013

************************************/

/*** Performs printing of variable(s) and adding/updating variables -
     calls mcshSort(), mcshFind(char type [], char name []), mcshUpdate(char type [], char name []. char value []) ***/
void mcshSet();

/*** Removes variable -
     calls mcshRemove(char type [], char name []) ***/
void mcshTes();

/*** Adds new variable -
     calls mcshInsert(char type, char name, char value) ***/
void addVar (char name [], char value []);

#endif
