# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 14:49:01 by cciapett          #+#    #+#              #
#    Updated: 2025/06/19 14:13:32 by cciapett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -g #-Werror

SRC = main.c main_utils.c philo.c eat.c sleep.c

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
