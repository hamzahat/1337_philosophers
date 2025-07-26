NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = # files
OBJ = $(SRC:.c=.o)
DEPS = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

flcean: clean
	rm -rf $(NAME)

re: flcean all

.PHONY: all clean flcean re

