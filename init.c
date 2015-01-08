#include "init.h"
#include "define.h"
#include "commands.h"
#include "set.h"
#include "alias.h"
#include "lexico.h"

void mcshInit (char* argv [])
{
    variableCount = 0;
    aliasCount = 0;

   // struct passwd *pw = getpwuid(getuid() );
   // char*  homedir = pw->pw_dir;
    //addVar ("HOME", homedir);

    fp = fopen ("rsrc.mcshrc", "r");
    while (fGet () != -1);
    fclose(fp);
    fpI = fopen (argv[1], "r");
}

void mcshStart ()
{
    printf ("----------------------------------------------- \n\n");
    printf ("MCSH Project 4 \n      Author: Dillon Murray \n      Class:  CSCE3600.S02 \n\n");
    printf ("----------------------------------------------- \n\n");
}

void mcshPrompt ()
{
    printf ("%s:~$ ", getcwd(directory, 512));
}

int fGet ()
{
    char* ptr;
    char  ch;
    char  tempVar [100];
    int   check;
    int   vCount;
    int   chCount;
    int   comString;
    int   i, varLength;

    clearCommand();
    vCount = 0;
    chCount = 0;
    comString = 0;
    parse:
    ch = getc(fp);
    while ((ch != '\n') && (ch != '?') && (chCount < 511) && (ch != EOF))
    {
        if (ch == '~')             // process comments
        {
            while (1)
            {
                ch = getc(fp);
                if ((ch == '\n') || (ch == '?'))
                {
                    return 1;
                }
            }
        }
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
            ch = getc(fp);
            while ((ch != '!') && (ch != ' ') && (ch != '\n'))
            {
                tempVar [vCount++] = ch;
                ch = getc(fp);
            }
            tempVar[vCount] = '\0';
            if (mcshFind ("variable", tempVar))
            {
                varLength = strlen (vCur->value);
                for (i = 0; i < varLength; i++)
                {
                    if ((vCur->value[i] != '{') && (vCur->value[i] != '}'))
                        {
                            buffer [chCount++] = vCur->value[i];
                        }
                }
            }
            else
            {
                printf("Variable %s not found.\n", tempVar);
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
                ch = getc(fp);
                if (ch == '\n')
                {
                    goto parse;
                }
            }
        }

        buffer [chCount++] = ch;
        ch = getc(fp);
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

    check = fCommands();
    if (check == -1)
    {
        return -1;
    }
    if ((ch == EOF) || (chCount == 0))
    {
        return -1;
    }
    if (ch == '?')
    {
        fGet();
    }

    return 1;
}

int fCommands ()
{
    if (strcmp("exit", commands [0]) == 0)
    {
        return -1;
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
    if (strcmp("mcshMalloc", commands [0]) == 0)
    {
        printf("Got mcshMalloc\n");
        return 1;
    }
    if (strcmp("mcshCalloc", commands [0]) == 0)
    {
        printf("Got mcshCalloc\n");
        return 1;
    }
    if (strcmp("mcshRealloc", commands [0]) == 0)
    {
        printf("Got mcshRealloc\n");
        return 1;
    }
    if (strcmp("mcshFree", commands [0]) == 0)
    {
        printf("Got mcshFree\n");
        return 1;
    }
    if (strcmp ("echo", commands [0]) == 0)
    {
        mcshEcho();
        return 1;
    }
    if (strcmp("mcsh", commands [0]) == 0)
    {
        printf ("Got external command.");
        return 1;
    }
    if (strcmp("where", commands [0]) == 0)
    {
//        mcshWhere();
        return 1;
    }
    if (checkAlias() == 1)
    {
        return 1;
    }

    return 0;
}




