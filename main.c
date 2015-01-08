#include "define.h"
#include "set.h"
#include "alias.h"
#include "lexico.h"
#include "init.h"
#include "commands.h"

/*** If argv[1] exists and is not a file, process argc as an external command ***/
//void handleExt (int argc, char* argv []);

/*** main function -
     start screen, initialization, argc check, input loop ***/
int main(int argc, char* argv[])
{
    mcshStart();
    mcshInit(argv);
 //   handleExt(argc, argv);

    while (1)
    {
        mcshPrompt();
        getCommand();
    }
    return 0;
}
/*
void handleExt (int argc, char* argv [])
{
    int i;
    if ((argc > 1) && (fp = NULL))
    {
        strcpy (buffer, argv[1]);
        for (i = 2; i < argc; i++)
        {
            strcat(buffer, " ");
            strcat(buffer, argv[i]);
        }

        printf("Got external command %s\n", buffer);
    }
}*/



