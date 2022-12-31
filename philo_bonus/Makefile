# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 14:35:11 by amorvai           #+#    #+#              #
#    Updated: 2022/12/31 05:14:00 by amorvai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo_bonus
CC		:= cc
CFLAGS	:= -I src/ -I lib/ -Wall -Wextra -Werror
VPATH	:= src/
OBJ_DIR	:= obj/

SRC		:=	main.c \
			philo_factory.c \
			philo_states.c \
			philo_utils.c \
			philo.c \
			utils.c

OBJ		:= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lpthread

$(OBJ_DIR): 
	mkdir obj

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) -MMD -MP $< -c -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

-include $(OBJ:.o=.d)
