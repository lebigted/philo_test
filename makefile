# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltestard <ltestard@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 09:13:24 by ltestard          #+#    #+#              #
#    Updated: 2023/11/10 11:38:24 by ltestard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -g  #-fsanitize=thread

RM = rm -f

SRC =   src/died_verif.c \
		src/display.c \
		src/forks.c \
		src/init.c \
		src/main.c \
        src/parsing.c \
		src/philo_actions.c \
		src/threads.c \
		src/utils.c 
		

			

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
