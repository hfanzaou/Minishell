/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:00:02 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 15:49:52 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdlib.h>
# include <dirent.h>
# include "lexer.h"

typedef struct token_s
{
	char			*value;
	int				err;
	int				here;
	struct token_s	*next;
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
	}				e_type;
}					t_token;

t_cmd	*init_cmd(char **cargs, int in, int out, int flag);
void	printf_token(t_token *token);
t_token	*tokenizer(t_lexer *lexer);
t_token	*token_init(char *val, int type, int flag, int here);
t_cmd	*ft_parse(t_token *token, t_cmd *cmd);
char	*ft_realloc(char *str, int j);
int		ft_strcmp(char *s1, char *s2);
char	*ft_expand(char *val, t_lexer **lexer, int j);
char	*ft_strdup2(const char *s);
int		ft_strrchr(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *cmd, char *arg, char *err);
char	*ft_strjoin2(char const *s1, char const *s2, int n);
int		ft_skip(char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*s_malloc(int size);
void	save_add(char *save);
char	*ft_itoa2(int n);
int		ft_isalnum(int an);
size_t	ft_strlen(const char *s);
char	*just_join(t_lexer *lexer, char *val, char *c);
char	*join_expand(t_lexer *lexer, char *val, char *val2);
char	*to_join(char c);
char	*remove_quotes(char c, t_lexer *lexer, char *str);
void	expand_exdollar(t_token **token, t_lexer *lexer);
int		executedollar(t_lexer *lexer);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
void	printf_token(t_token *token);
void	token_redin(t_lexer *lexer, t_token **token, int i);
void	token_redout(t_token **token, int i);
void	token_pipe(t_token **token);
int		what_redt(char c, char nc);
void	specialsymbols(t_lexer *lexer, t_token **token, int type);
void	handler(int i);
void	ft_free2(void **str);
void	exit_bash(char *line);

#endif  
