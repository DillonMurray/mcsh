#include "set.h"
#include "define.h"
#include "lexico.h"

void mcshSet()
{
    variable* vPtr;

    if (commandCount == 0)
    {
        printf("Command count should not be 0 in mcshSet.\n");
        return;
    }

/****** print all variables ******/
    if (commandCount == 1)
    {
        if (variableCount > 1)
        {
            mcshSort();
        }
        for (vPtr = vHead; vPtr != NULL; vPtr = vPtr->next)
        {
            if ((strcmp (vPtr->name, "") != 0) && (vPtr != NULL))
                printf ("%s %s\n", vPtr->name, vPtr->value);
        }
        return;
    }

/****** print specific variable ******/
    if (commandCount == 2)
    {
        if (mcshFind("variable", commands[1]))
        {
           printf ("%s %s\n", vCur->name, vCur->value);
        }
        else
        {
            printf ("Variable %s not found.\n", commands[1]);
        }
        return;
    }

/****** add or update variable ******/

    /* check if commands [1] name already exists, update value accordingly */
    if (mcshFind ("variable", commands[1]))
    {
        mcshUpdate ("variable", vCur->name, commands [2]);
    }
    else
    {
        addVar (commands[1], commands[2]);
    }
    return;
}

void mcshTes()
{
    mcshRemove ("variable", commands[1]);
    return;
}

void addVar(char name [], char value [])
{
    mcshInsert("variable", name, value);
    return;
}


