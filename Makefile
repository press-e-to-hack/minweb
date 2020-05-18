CC = gcc
CFLAGS = -g -pedantic -std=c99
NAME = minweb
PANDOC = pandoc

all: $(NAME)

$(NAME): src/main.c
	$(CC) $(CFLAGS) -o $(NAME) $^

man:
	${PANDOC} -s -t man doc/man/$(NAME).1.md -o $(NAME).1

clean:
	rm -rf *.o $(NAME)
