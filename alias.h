#ifndef ALIAS_H
#define ALIAS_H

/************************************

alias.h
- contains alias related protoypes
- often calls lexico.h functions
- last modified: Apr 14, 2013

************************************/

/*** Performs printing of alias(es) and adding/updating aliases -
     calls mcshSort(), mcshFind(char type [], char name []), mcshUpdate(char type [], char name []. char value []) ***/
void mcshAlias ();

/*** Removes alias -
     calls mcshRemove(char type [], char name []) ***/
void mcshSaila ();

/*** Adds new alias -
     calls mcshInsert(char type, char name, char value) ***/
void addAlias (char name [], char value []);

#endif
