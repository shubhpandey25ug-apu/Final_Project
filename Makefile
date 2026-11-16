Bank: main.c linkedlist.c file_io.c transaction.c ui.c bank.h
	gcc -Wall -Wextra -std=c11 main.c linkedlist.c file_io.c transaction.c ui.c -o Bank -lm

clean:
	rm -f Bank