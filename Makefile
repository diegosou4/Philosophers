# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diegmore <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:12:34 by diegmore          #+#    #+#              #
#    Updated: 2024/04/23 16:49:13 by diegmore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = philo

CC = cc

CFLAGS = #-Wall -Wextra -Werror

SRC = ft_check.c ft_parse.c

SRC_DIR = $(addprefix ./src/, $(SRC))

SRCOBJ = OBJ/

OBJ = $(addprefix $(SRCOBJ), $(SRC:./src/%.c=%.o))

all: $(NAME)
	${CC} main.c ${SRC_DIR} ${CFLAGS}


