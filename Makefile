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

CFLAGS = -pthread  -Wall -Wextra -Werror -I./includes

SRC = ft_parse.c ft_start.c ft_mutex.c ft_threads.c  ft_macros.c \
		ft_main.c ft_timesync.c ft_free.c

SRC_DIR = $(addprefix ./src/, $(SRC))

SRCOBJ = obj/
OBJ = $(addprefix $(SRCOBJ), $(SRC:/src/%.c=%.o))

all: $(NAME)
$(NAME): $(OBJ)
	${CC} ${CFLAGS} main.c ${OBJ} -o $(NAME)

$(SRCOBJ)%.o: src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf $(SRCOBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

