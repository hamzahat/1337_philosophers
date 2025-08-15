# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 09:23:11 by hbenmoha          #+#    #+#              #
#    Updated: 2025/08/15 13:35:13 by hbenmoha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRC = philo_init.c philo_main.c philo_parsing.c philo_utils_1.c philo_utils_2.c getters_and_setters_1.c getters_and_setters_2.c ft_safe_malloc.c philo_dining.c
OBJ = $(SRC:.c=.o)
DEPS = philo_header.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
