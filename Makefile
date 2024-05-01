# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:12:34 by diegmore          #+#    #+#              #
#    Updated: 2024/05/01 11:08:46 by diemorei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = philo

CC = cc -pthread

CFLAGS = #-Wall -Wextra -Werror

SRC = ft_check.c ft_parse.c ft_start.c ft_time.c

SRC_DIR = $(addprefix ./src/, $(SRC))

SRCOBJ = OBJ/

OBJ = $(addprefix $(SRCOBJ), $(SRC:./src/%.c=%.o))

all: $(NAME)
	${CC} main.c ${SRC_DIR} ${CFLAGS}


