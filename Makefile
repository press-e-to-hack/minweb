CC = gcc
CFLAGS = -g -pedantic -std=c99
NAME = minweb

all: $(NAME)

$(NAME): src/main.c
	$(CC) $(CFLAGS) -o $(NAME) $^

clean:
	rm -rf *.o $(NAME)
