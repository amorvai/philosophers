# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/25 14:35:11 by amorvai           #+#    #+#              #
#    Updated: 2022/12/28 02:21:27 by amorvai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= cc
CFLAGS	:= -I src/ -I lib/ -Wall -Werror -Wextra
VPATH	:= src/
OBJ_DIR	:= obj/

SRC		:=	main.c \
			philo.c \
			set_up.c \
			state.c \
			boss.c \
			util.c \

OBJ		:= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR): 
	mkdir obj

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re