/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:55:56 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 14:33:50 by hfanzaou         ###   ########.fr       */
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

typedef struct envlist
{
	char			*key;
	char			*value;
	char			sep;
	struct envlist	*next;
}					t_envlist;

typedef struct g_global
{
	t_envlist	*envlist;
	int			env_size;
	int			exit_status;
	void		*to_free[10000];
	int			index;
}				t_global;

typedef struct lexer_s
{
	char	*src;
	char	c;
	int		size;
	int		f;
	int		i;
}			t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	struct s_cmd	*next;
}					t_cmd;
t_global			g_global;

t_lexer	*ft_lexer(char *src);
void	lexer_advance(t_lexer **lexer);
t_lexer	*lexer_ntoken(t_lexer *lexer);
void	lexer_advance_i(t_lexer **lexer, int n);
char	nextcval(t_lexer *lexer, int i);
void	excute(t_cmd *cmd_lst);
void	envlist_init(char **env);
void	ft_free(char **str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

#endif