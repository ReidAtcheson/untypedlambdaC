CC := clang
CFLAGS := -c -g -Wall -pedantic



main : main.o purelambda.o examples.o
	$(CC) -o main main.o purelambda.o examples.o

main.o : main.c
	$(CC) $(CFLAGS) main.c -o main.o

examples.o : examples.c
	$(CC) $(CFLAGS) examples.c -o examples.o

purelambda.o : purelambda.c
	$(CC) $(CFLAGS) purelambda.c -o purelambda.o



.PHONY : clean


clean :
	rm -rf ./main
	rm -rf ./*.dSYM
	rm -rf ./*.o
