CC := clang
CFLAGS := -c -g -Wall -pedantic



main : main.o purelambda.o examples.o utlambda_yac.o utlambda_lex.o
	$(CC) -o main main.o purelambda.o examples.o utlambda_lex.o utlambda_yac.o -ll

main.o : main.c
	$(CC) $(CFLAGS) main.c -o main.o

examples.o : examples.c
	$(CC) $(CFLAGS) examples.c -o examples.o

purelambda.o : purelambda.c
	$(CC) $(CFLAGS) purelambda.c -o purelambda.o

utlambda_yac.o : utlambda_yac.c
	$(CC) $(CFLAGS) utlambda_yac.c -o utlambda_yac.o

utlambda_lex.o : utlambda_lex.c
	$(CC) $(CFLAGS) utlambda_lex.c -o utlambda_lex.o

utlambda_yac.c : utlambda.y
	bison -d -o utlambda_yac.c utlambda.y

utlambda_lex.c : utlambda.l
	flex -o utlambda_lex.c utlambda.l



.PHONY : clean


clean :
	rm -rf ./utlambda_yac.h
	rm -rf ./utlambda_yac.c
	rm -rf ./utlambda_lex.c
	rm -rf ./main
	rm -rf ./*.dSYM
	rm -rf ./*.o
