# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chiara_ciapetti <chiara_ciapetti@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 14:49:01 by cciapett          #+#    #+#              #
#    Updated: 2025/06/22 21:46:45 by chiara_ciap      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread

SRC = main.c main_utils.c philo.c eat.c sleep.c death.c one_philo.c philo_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
