#include "lexico.h"
#include "define.h"

void mcshHead (char type [])
{
    if (strcmp(type, "variable") == 0)
    {
        vCur = vHead;
        return;
    }
    else if (strcmp(type, "alias") == 0)
    {
        aCur = aHead;
        return;
    }
    else
        printf ("You did not declare variable or alias.\n");
}

int mcshFind(char type [], char name [])
{
    int i;

    if (strcmp(type, "variable") == 0)
    {
        for (i = 0; i < variableCount; i++)
                {
                    vCur = userVariables [i];
                    if (strcmp (name, vCur->name) == 0)
                    {
                       return 1;
                    }
                }
        vCur = NULL;
        return 0;
    }
    else if (strcmp(type, "alias") == 0)
    {
        for (i = 0; i < aliasCount; i++)
                {
                    aCur = userAliases [i];
                    if (strcmp (name, aCur->name) == 0)
                    {
                       return 1;
                    }
                }
        aCur = NULL;
        return 0;
    }

    return 0;
}

void mcshInsert(char type [], char name [], char value [])
{
    if ((strcmp (type, "variable") == 0) || (strcmp (type, "var") == 0))
    {
        userVariables [variableCount] = malloc(sizeof(variable));
        userVariables [variableCount]->name = malloc(strlen(name));
        userVariables [variableCount]->value = malloc(strlen(value));
        strcpy (userVariables [variableCount]->name, name);
        strcpy (userVariables [variableCount]->value, value);
        vCur = userVariables [variableCount];
        if (variableCount == 0)
        {
            vHead = vCur;
            vHead->next = NULL;
        }
        else
        {
            vCur->prev = userVariables [variableCount-1];
            userVariables [variableCount-1]->next = vCur;
            vCur->next = NULL;
        }
        variableCount++;
        return;
    }
    else if ((strcmp (type, "alias") == 0) || (strcmp (type, "ali") == 0))
    {
        userAliases [aliasCount] = malloc(sizeof(alias));
        userAliases [aliasCount]->name = malloc(strlen(name));
        userAliases [aliasCount]->value = malloc(strlen(value));
        strcpy (userAliases [aliasCount]->name, name);
        strcpy (userAliases [aliasCount]->value, value);
        aCur = userAliases [aliasCount];
        if (aliasCount == 0)
        {
            aHead = aCur;
            aHead->next = NULL;
        }
        else
        {
            aCur->prev = userAliases [aliasCount-1];
            userAliases [aliasCount-1]->next = aCur;
            aCur->next = NULL;
        }
        aliasCount++;
        return;
    }
    else
        printf ("You did not declare variable or alias.\n");

    return;
}

void mcshNext (char type [])
    {
        if ((strcmp (type, "variable") == 0) || (strcmp (type, "var") == 0))
        {
            if (vCur->next != NULL)
                vCur = vCur->next;
            return;
        }
        else if ((strcmp (type, "alias") == 0) || (strcmp (type, "ali") == 0))
        {
            if (aCur->next != NULL)
                aCur = aCur->next;
            return;
        }
        else
            printf ("You did not declare variable or alias.\n");

        return;
    }

void mcshRemove (char type [], char name [])
{
    int i, j;
    if (strcmp(type, "variable") == 0)
    {
        if (mcshFind(type, name))
        {
            for (i = 0; i < variableCount; i++)
            {
                if (strcmp(userVariables[i]->name, name) == 0)
                {
                    j = i;
                    while ((userVariables[j+1] != NULL) && (j < variableCount))
                    {
                        userVariables [j] = userVariables[j+1];
                        j++;
                    }
                    userVariables[j]->next = NULL;
                    variableCount--;
                }
            }
            return;
        }
    }
    else if (strcmp(type, "alias") == 0)
    {
        if (mcshFind(type, name))
        {
            for (i = 0; i < aliasCount; i++)
            {
                if (strcmp(userAliases[i]->name, name) == 0)
                {
                    j = i;
                    while ((userAliases[j+1] != NULL) && (j < aliasCount))
                    {
                        userAliases [j] = userAliases[j+1];
                        j++;
                    }
                    userAliases[j]->next = NULL;
                    aliasCount--;
                }
            }
            return;
        }
    }
    else
        printf ("You did not declare variable or alias.\n");

    return;
}

void mcshSort ()
    {
        alias* aPtr;
        variable* vPtr;
        int i, j, minimum;

        if (variableCount > 0)
        {
            for (i = 0; i < variableCount; i++)
            {
                minimum = i;
                for (j = i+1; j < variableCount; j++)
                {
                    if (strcmp(userVariables[j]->name, userVariables[minimum]->name) < 0)
                    {
                        minimum = j;
                    }
                }
                vPtr = userVariables[minimum];
                userVariables[minimum] = userVariables[i];
                userVariables[i] = vPtr;
            }
            i = 0;
            while(userVariables[i] != NULL)
            {
                if ((i == 0) && (variableCount > 1))
                {
                    vHead = userVariables[i];
                    userVariables[i]->next = userVariables[i+1];
                }
                else
                {
                    userVariables[i]->prev = userVariables[i-1];
                    if (userVariables[i+1] != NULL)
                    {
                        userVariables[i]->next = userVariables[i+1];
                    }
                }
                i++;
            }
            userVariables[i-1]->next = NULL;
        }
        if (aliasCount > 0)
        {
            for (i = 0; i < aliasCount; i++)
            {
                minimum = i;
                for (j = i+1; j < aliasCount; j++)
                {
                    if (strcmp(userAliases[j]->name, userAliases[minimum]->name) < 0)
                    {
                        minimum = j;
                    }
                }
                aPtr = userAliases[minimum];
                userAliases[minimum] = userAliases[i];
                userAliases[i] = aPtr;
            }
            i = 0;
            while(userAliases[i] != NULL)
            {
                if ((i == 0) && (aliasCount > 1))
                {
                    aHead = userAliases[i];
                    aHead->next = userAliases[i+1];
                }
                else
                {
                    userAliases[i]->prev = userAliases[i-1];
                    if (userAliases[i+1] != NULL)
                    {
                        userAliases[i]->next = userAliases[i+1];
                    }
                }
                i++;
            }
            userAliases[i-1]->next = NULL;
        }
        return;
    }

void mcshUpdate (char type [], char name [], char value [])
{
    if ((strcmp (type, "variable") == 0) || (strcmp (type, "var") == 0))
    {
        mcshFind (type, name);
        vCur->name = realloc (vCur->name, (strlen(name)));
        vCur->value = realloc (vCur->value, (strlen(value)));
        strcpy(vCur->name, name);
        strcpy(vCur->value, value);
        return;
    }
    else if ((strcmp (type, "alias") == 0) || (strcmp (type, "ali") == 0))
    {
        mcshFind (type, name);
        aCur->name = realloc (aCur->name, (strlen(name)));
        aCur->value = realloc (aCur->value, (strlen(value)));
        strcpy(aCur->name, name);
        strcpy(aCur->value, value);
        return;
    }
    else
        printf ("You did not declare variable or alias.\n");

    return;
}
