CC 		= gcc
CFLAGS 		= -g -pedantic -std=c99
NAME 		= minweb

program: main.c
	$(CC) $(CFLAGS) -o $(NAME) $^

clean:
	rm -rf *.o $(NAME)
