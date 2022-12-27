/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:00:02 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/25 05:33:36 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdlib.h>
# include "lexer.h"
# include <dirent.h>

typedef struct token_s
{
	char *value;
	int		err;
	int		here;
	struct token_s *next;
	enum
	{
		STRING,
		SINGLE_Q,
		DOUBLE_Q,
		RED_IN,
		RED_OUT,
		RED_IN2,
		RED_OUT2,
		PIPE,
		DOLLAR,
		EXIT,
		EXDOLLAR,
		END
	} type;
}	token_t;

t_cmd *init_cmd(char **cargs, int in, int out, int flag);
void printf_token(token_t *token);
token_t *tokenizer(t_lexer *lexer);
token_t *token_init(char *val, int type, int flag, int here);
t_cmd *ft_parse(token_t *token, t_cmd *cmd);
char	*ft_realloc(char *str, int j);
int	ft_strcmp(char *s1, char *s2);
char	*ft_expand(char *val, char **env, t_lexer **lexer, int j);
char	*ft_strdup(const char *s);
int		ft_strrchr(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *cmd, char *arg, char *err);
char	*ft_strjoin2(char const *s1, char const *s2, int n);
int 	ft_skip(char *str);
int	ft_memcmp(const void *s1, const void *s2, size_t n);
void	free_hack(char *str);
void	*s_malloc(int size);
void	save_add(char *save);
# endif  
