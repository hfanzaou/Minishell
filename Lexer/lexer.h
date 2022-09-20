/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:55:56 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/09 15:55:58 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <ctype.h>

# include <string.h>

typedef struct lexer_s
{
	char *src;
	char c;
	int size;
	int i;
} t_lexer;

typedef struct s_cmd
{
	char **cmd;
	int in;
	int out;
	int fd;
	struct s_cmd *next;
}	t_cmd;

t_lexer *lexer(char *src);
void	lexer_step(t_lexer **lexer);
t_lexer *lexer_ntoken(t_lexer *lexer);
# include "token.h"
#endif