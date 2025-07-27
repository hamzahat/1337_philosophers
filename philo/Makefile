# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 18:35:35 by hbenmoha          #+#    #+#              #
#    Updated: 2025/07/27 18:35:38 by hbenmoha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
