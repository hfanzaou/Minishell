# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajana <ajana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:03:01 by ajana             #+#    #+#              #
#    Updated: 2022/12/23 02:20:24 by ajana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror


SRCS = execution/minishell.c execution/export.c execution/builtins.c execution/envlist_tools.c \
	execution/tools.c Lexer/tokenizer.c Lexer/main.c Lexer/Lexer.c Lexer/token.c Lexer/parse.c

LIBFT = libft/libft.a

LIBS = -L/usr/include -lreadline -Llibft -lft

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft/

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -g3 -fsanitize=address $(OBJS) $(LIBS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C libft clean

fclean : clean
	$(RM) $(NAME)

re : fclean all
