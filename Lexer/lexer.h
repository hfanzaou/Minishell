/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:55:56 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/27 00:18:20 by ajana            ###   ########.fr       */
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
# include <fcntl.h>
//# include "parse.h"
# define BGRN "\e[1;32m"
# define reset "\e[0m"

typedef	struct envlist
{
	char			*key;
	char			*value;
	char			sep;
	struct	envlist	*next;
}	t_envlist;

typedef	struct global
{
	t_envlist	*envlist;
	char		**envp;
	int			env_size;
	int			exit_status;
} t_global;

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
	int err;
	struct s_cmd *next;
}	t_cmd;

t_global	global;

t_lexer *ft_lexer(char *src);
void	lexer_advance(t_lexer **lexer);
t_lexer *lexer_ntoken(t_lexer *lexer);
void 	lexer_advance_i(t_lexer **lexer, int n);
char 	nextcval(t_lexer *lexer, int i);
void	excute(t_cmd *cmd_lst);
void	envlist_init();
void	ft_free(char **str);

# include "token.h"
#endif