# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajana <ajana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:03:01 by ajana             #+#    #+#              #
#    Updated: 2022/12/12 23:00:38 by ajana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror


SRCS = execution/minishell.c execution/builtins.c Lexer/tokenizer.c \
	Lexer/main.c Lexer/Lexer.c Lexer/token.c Lexer/parse.c

LIBFT = libft/libft.a

LIBS = -L/usr/include -lreadline -Llibft -lft

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft/

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -fsanitize=address $(OBJS) $(LIBS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all