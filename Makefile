# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajana <ajana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:03:01 by ajana             #+#    #+#              #
#    Updated: 2022/12/28 05:12:14 by ajana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror #-fsanitize=address  #-I/goinfre/ajana/.brew/opt/readline/include


SRCS = execution/execution.c execution/builtins_export.c execution/builtins.c execution/envlist_tools.c \
	execution/tools.c execution/builtins_2.c  execution/builtins_cd.c Lexer/tokenizer.c Lexer/main.c Lexer/Lexer.c Lexer/token.c Lexer/parse.c \
	Lexer/utils.c Lexer/expand.c Lexer/ft_itoa2.c

LIBFT = libft/libft.a

LIBS = -L/usr/include -lreadline -Llibft -lft  #-L/goinfre/ajana/.brew/opt/readline/lib

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft/

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C libft clean

fclean : clean
	$(RM) $(NAME)

re : fclean all
