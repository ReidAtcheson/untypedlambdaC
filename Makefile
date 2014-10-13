

CC := clang
CFLAGS := -c -g



main : main.o purelambda.o
	$(CC) -o main main.o purelambda.o

main.o : main.c
	$(CC) $(CFLAGS) main.c -o main.o


purelambda.o : purelambda.c
	$(CC) $(CFLAGS) purelambda.c -o purelambda.o



.PHONY : clean


clean :
	rm -rf ./main
	rm -rf ./*.dSYM
	rm -rf ./*.o
