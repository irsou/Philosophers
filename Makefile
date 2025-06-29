# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 10:02:25 by isousa-s          #+#    #+#              #
#    Updated: 2025/05/24 10:02:25 by isousa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/aux_functions.c \
	src/clean_data.c \
	src/init.c \
	src/main.c \
	src/threads.c \
	src/tracking.c \
	src/tracking_aux.c \
	src/utils.c \
	src/validate_args.c \

OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Werror -Wextra -Iincludes
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

src/%.o: src/%.c includes/philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re