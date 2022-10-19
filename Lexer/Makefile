# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 02:39:03 by hfanzaou          #+#    #+#              #
#    Updated: 2022/09/18 02:39:05 by hfanzaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = tokenizer.c Lexer.c main.c token.c parse.c
NAME = Minishell
FLAGS = -Wall -Werror -Wextra -L/usr/include -lreadline -fsanitize=address
CC = gcc

all : $(NAME)

$(NAME) : $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)