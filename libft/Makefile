# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajana <ajana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 03:08:30 by ajana             #+#    #+#              #
#    Updated: 2021/11/17 21:15:42 by ajana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
   ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
   ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS_OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(SRCS_OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $<
	ar -rc $(NAME) $@

bonus: $(BONUS_OBJS)

re: fclean all

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(SRCS_OBJS) $(BONUS_OBJS)

.PHONY: all clean fclaen re bonus
