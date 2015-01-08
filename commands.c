#include "commands.h"
#include "define.h"
#include "set.h"
#include "alias.h"
#include "lexico.h"
#include "init.h"

/***** make sure acceptable command was given *****/
void checkCommand ()
{
    if (mcshCommands () == 0)
    {
        printf ("Command %s failed.\n", commands [0]);
    }

}

/***** clear command/buffer info. Prepare for next parse *****/
void clearCommand ()
{
    int i;

    for (i = 0; i < commandCount; i++)
    {
        strcpy(commands [i], "");
    }

    commandCount = 0;
    strcpy(buffer, "");
}

/***** parse input (from arg file or interactive), replace @var, split commands *****/
void getCommand ()  // Parse command input
{
    char* ptr;
    char  ch;
    char  tempVar [100];
    int   vCount;
    int   chCount;
    int   comString;
    int   i, varLength;

    clearCommand();
    vCount = 0;
    chCount = 0;
    comString = 0;
    parse:
    if (fpI != NULL)
    {
        ch = getc(fpI);
    }
    else
    {
       ch = getchar();
    }
    while ((ch != '\n') && (ch != '?') && (chCount < 511) && (ch != EOF))
    {
        if (ch == '~')
        {
            while (1)
            {
                if (fpI != NULL)
                    {
                        ch = getc(fpI);
                    }
                    else
                    {
                       ch = getchar();
                    }
                if ((ch == '\n') || (ch == '?'))
                {
                    return;
                }
            }
        }
        // what characters are affected by being in a complex string?
        if (ch == '{')                          // now in a complex string
        {
            comString = 1;
        }
        if (ch == '}')                          // leaving complex string
        {
            comString = 0;
        }
        if (ch == '@')                          // with @, insert referenced variable's value
        {
            if (fpI != NULL)
            {
                ch = getc(fpI);
            }
            else
            {
               ch = getchar();
            }
            while ((ch != '!') && (ch != ' ') && (ch != '\n'))
            {
                tempVar [vCount++] = ch;
                if (fpI != NULL)
                {
                    ch = getc(fpI);
                }
                else
                {
                   ch = getchar();
                }
            }
            tempVar[vCount] = '\0';
            if (mcshFind ("variable", tempVar))
            {
               // vcount = 0;
                varLength = strlen(vCur->value);
                for (i = 0; i < varLength; i++)
                {
                    if (vCur->value[i] != '{' && vCur->value[i] != '}')
                        {
                            buffer [chCount++] = vCur->value[i];
                        }
                }
            }
            else
            {
                printf("Variable %s doesn't exist.\n", tempVar);
            }
            if ((ch == '!') || ((ch == ' ') && (comString == 1)))
            {
                buffer [chCount++] = ch;
            }
            else if (ch == '\n')
            {
                break;
            }
            strcpy (tempVar, "");
            vCount = 0;
            goto parse;
        }
        if (ch == '$')                          // on '$' go to end of line before continuing to parse
        {
            while (1)
            {
                if (fpI != NULL)
                    {
                        ch = getc(fpI);
                    }
                    else
                    {
                       ch = getchar();
                    }
                if (ch == '\n')
                {
                    goto parse;
                }
            }
        }

        buffer [chCount++] = ch;
        if (fp != NULL)
            {
                ch = getc(fp);
            }
            else
            {
                ch = getchar();
            }
    }

    if (ch == EOF)                              // if parsing from file (most likely command line argument) quit on EOF
    {
        exit(0);
    }
    buffer [chCount] = '\n'; // concatenating \n might be a mistake. \0 might be better.

    ptr = strtok(buffer, " ");
    while(ptr != NULL) // Split buffer into commands
    {
        commands [commandCount] = ptr;
        if (commandCount < 1)
        {
            ptr = strtok(NULL, " ");
        }
        else
        {
            ptr = strtok(NULL, "\n");
        }
        commandCount++;
    }
    buffer [chCount] = '\0';

    checkCommand();                             // calls mcshCommands()

    if (ch == '?')                              // parse next command on '?'
    {
        getCommand();
    }
}

/***** process initial command input *****/
int mcshCommands ()
{
    if (strcmp("exit", commands [0]) == 0)
    {
        exit(0);
    }
    if (strcmp("set", commands [0]) == 0)
    {
        mcshSet();
        return 1;
    }
    if (strcmp("tes", commands [0]) == 0)
    {
        mcshTes();
        return 1;
    }
    if (strcmp("alias", commands [0]) == 0)
    {
        mcshAlias();
        return 1;
    }
    if (strcmp("saila", commands [0]) == 0)
    {
        mcshSaila();
        return 1;
    }
    if (strcmp("mcsh", commands [0]) == 0)
    {
        printf ("Got external command.");
        return 1;
    }
    if (strcmp("where", commands [0]) == 0)
    {
        mcshWhere();
        return 1;
    }
    if (strcmp ("echo", commands [0]) == 0)
    {
        mcshEcho();
        return 1;
    }
    if (checkAlias() == 1)
    {
        return 1;
    }
    /*if (mcshExternal() != NULL)
    {
        return 1;
    }*/

    return 0;
}

/***** check for alias value and insert into buffer *****/
int checkAlias()
{
    int i;
    char tempBuffer [512];
    char* ptr;

    if (mcshFind ("alias", commands[0]))
    {
        strcpy (tempBuffer, aCur->value);
        i = 1;
        while (strcmp(commands[i], "") != 0)
        {
            strcat (tempBuffer, " ");
            strcat (tempBuffer, commands[i]);
            i++;
        }
        clearCommand ();
        strcpy (buffer, tempBuffer);
        buffer [strlen(tempBuffer)] = '\n';
        ptr = strtok(buffer, " ");
        while(ptr != NULL) // Split buffer into commands
        {
            commands [commandCount] = ptr;
            if (commandCount < 1)
            {
                ptr = strtok(NULL, " ");
            }
            else
            {
                ptr = strtok(NULL, "\n");
            }
            commandCount++;
        }
        buffer [strlen(tempBuffer)] = '\0';
        if (fp != NULL)
        {
            fCommands();
        }
        else
            checkCommand();
        return 1;
    }
    return 0;
}

void mcshEcho ()
{
    char tempBuffer [512];

    if (commandCount == 1)
    {
        printf ("\n");
    }
    else
    {
        strcpy (tempBuffer, commands[1]);
        if (commandCount >= 2)
        {
            strcat (tempBuffer, " ");
            strcat (tempBuffer, commands[2]);
        }
        printf ("%s\n", tempBuffer);
    }

}

void mcshWhere ()
{
    void* ptr;
    struct stat fInfo;
    char cmd [100];
    char tempPath [512];

    if (mcshFind("alias", commands[2]))
    {
        strcpy(cmd, aCur->value);
    }
    if ((strcmp(cmd, "set") == 0) || (strcmp(cmd, "alias") == 0) || (strcmp(cmd, "echo") == 0) || (strcmp(cmd, "tes") == 0) ||
        (strcmp(cmd, "saila") == 0) || (strcmp(cmd, "where") == 0))
    {
        printf ("%s is an internal command.\n", cmd);
    }
    else if ((ptr = strtok(commands[2], "/")) == NULL)
    {
        if (mcshFind ("variable", "PATH"))
        {
            ptr = strtok (vCur->value, "! ");
            while (ptr != NULL)
            {
                strcpy(tempPath, ptr);
                strcat(tempPath, commands[2]);
                if (stat(tempPath, &fInfo) == 0)
                {
                    printf ("%s\n", tempPath);
                }
                ptr = strtok(NULL, "! ");
            }
        }
        // check PATH variable
    }
    else
    {
        strcpy(tempPath, commands[2]);
        if (stat (tempPath, &fInfo) == 0)
        {// look at absolute or relative location
            printf ("%s\n", tempPath);
        }
        else
        {
            printf ("%s not found.\n", tempPath);
        }
    }
}











