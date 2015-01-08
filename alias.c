#include "alias.h"
#include "define.h"
#include "lexico.h"

void mcshAlias()
{
    alias* aPtr;

/****** print all aliases ******/
    if (commandCount == 1)
    {
        if (aliasCount > 1)
        {
            mcshSort();
        }
        for (aPtr = aHead; aPtr != NULL; aPtr = aPtr->next)
        {
            if ((strcmp (aPtr->name, "") != 0) && (aPtr != NULL))
                printf ("%s %s\n", aPtr->name, aPtr->value);
        }
        return;
    }

/****** print specific alias ******/
    if (commandCount == 2)
    {
        if (mcshFind("alias", commands[1]))
        {
           printf ("%s %s\n", aCur->name, aCur->value);
        }
        else
        {
            printf ("Alias %s not found.\n", commands[1]);
        }
        return;
    }

/****** add or update alias ******/

    /* check if commands [1] name already exists, update value accordingly */
    if (mcshFind ("alias", commands[1]))
    {
        mcshUpdate ("alias", aCur->name, commands[2]);
    }
    else
    {
        addAlias (commands[1], commands[2]);
    }
    return;
}

void mcshSaila()
{
    mcshRemove ("alias", commands[1]);
    return;
}

void addAlias (char name [], char value [])
{
    mcshInsert("alias", name, value);
    return;
}

