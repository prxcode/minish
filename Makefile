CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
NAME = minish
SRC = src/main.c src/input.c src/executor.c src/builtins.c src/pipes.c src/signals.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -Iinclude $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re