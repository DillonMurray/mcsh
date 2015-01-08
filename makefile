iDir = ../include
sDir = ../src
oDir = ../obj

prog4_dam0271: main.o alias.o commands.o define.o init.o lexico.o set.o
	gcc main.o alias.o commands.o define.o init.o lexico.o set.o -o prog4_dam0271
	
alias.o: alias.h alias.c define.h lexico.h
	gcc -c alias.c
	
commands.o: commands.h commands.c define.h set.h alias.h lexico.h
	gcc -c commands.c

define.o: define.h define.c
	gcc -c define.c
	
init.o: init.h init.c commands.h define.h set.h alias.h lexico.h
	gcc -c init.c

main.o: main.c define.h set.h alias.h lexico.h init.h commands.h
	gcc -c main.c

lexico.o: lexico.h lexico.c define.h
	gcc -c lexico.c

set.o: set.h set.c define.h lexico.h
	gcc -c set.c
	
clean:
	rm -f *.o




	




