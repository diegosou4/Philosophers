# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:12:34 by diegmore          #+#    #+#              #
#    Updated: 2024/05/29 18:44:29 by diegmore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -g 

CFLAGS = -pthread  -Wall -Wextra -Werror -I./includes #-fsanitize=thread

SRC = ft_parse.c ft_start.c ft_mutex.c ft_threads.c  ft_macros.c \
		ft_main.c ft_timesync.c ft_free.c

SRC_DIR = ./src/
OBJ_DIR = ./obj/

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)
$(NAME): $(OBJ)
	${CC} ${CFLAGS} main.c ${OBJ} -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

