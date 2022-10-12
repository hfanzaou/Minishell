/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:17:24 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/18 02:17:26 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*b;

	c = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (c[i] != b[i])
			return (c[i] - b[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	char	*p;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dst = malloc(i * sizeof(char) + 1);
	if (dst == NULL)
		return (0);
	p = dst;
	while (*s)
	{
		*dst++ = *s++;
	}
	*dst = '\0';
	return (p);
}

void printf_token(token_t *token)
{
	printf("In token\n");
	while (token)
	{
		printf("type  = %d\n", token->type);
		printf("value = %s\n", token->value);
		token = token->next;
	}
}

token_t	*ft_lstlast(token_t *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	ft_lstadd_back(token_t **lst, token_t *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

int ft_size(t_lexer *lexer)
{
	int i;

	i = 0;
	while (lexer->src[lexer->i + i] && (lexer->src[lexer->i + i] != '\'' || lexer->src[lexer->i + i] != '\"'))
		i++;	
	if (!lexer->src[i])
		return (-1);
	return (i);	
}

char	*ft_expand(t_lexer *lexer, char **env)
{
	char *s;
	int i;
	int l;

	i = 0;
	s = malloc(sizeof(char) * ft_size(lexer) + 1);
	if (!s)
		return NULL;
	while (lexer->src[lexer->i] && lexer->c != '\"' && lexer->c != ' ' && lexer->c != '\t')
	{
		s[i] = lexer->c;
		lexer_step(&lexer);
		i++;
	}
	s[i] = '\0';
	l = strlen(s);
	while (env[i])
	{
		if (!ft_memcmp(env[i], s, l))
			return (&env[i][l + 1]);
		i++;
	}
	return (NULL);
}

void	token_sq(token_t **token, t_lexer *lexer)
{	
	token_t *oneuse;
	char *val;
	int type;
	int size;
	
	lexer_step(&lexer);
	if (!lexer->c)
		return ;
	size = 0;
	type = SINGLE_Q;
	val = malloc(sizeof(char) * ft_size(lexer) + 1);
	while (lexer->c != '\'')
	{
		val[size] = lexer->c;
		size++;
		lexer_step(&lexer);
		if (!lexer->c)
			return ;
	}
	val[size] = '\0';	
	oneuse = token_init(val, type);
	ft_lstadd_back(token, oneuse);
}

void	token_dq(token_t **token, t_lexer *lexer, char **env)
{	
	token_t *oneuse;
	char *val;
	int type;
	int size;

	lexer_step(&lexer);
	if (!lexer->c)
	 	return ;
	(void)env;	
	size = 0;
	type = DOUBLE_Q;
	val = malloc(sizeof(char) * ft_size(lexer) + 1);
	if (!val)
		return ;
	while (lexer->c != '\"')
	{
		if (lexer->c == '$')
		{
			size = -1;
			lexer_step(&lexer);
			val = ft_expand(lexer, env);
			break;
		}
		val[size] = lexer->c;
		size++;
		lexer_step(&lexer);
		if (!lexer->c)
			return ;
	}
	if (size != -1)
		val[size] = '\0';	
	oneuse = token_init(val, type);
	ft_lstadd_back(token, oneuse);
}

void	token_pipe(token_t **token)
{
	token_t *oneuse;
	char *val;
	int type;

	type = PIPE;
	oneuse = NULL;
	val = ft_strdup("|");
	oneuse = token_init(val, type);
	ft_lstadd_back(token, oneuse);

}

void	token_redout(token_t **token, int i)
{
	token_t *oneuse;
	char *val;
	int type;

	type = RED_IN;
	oneuse = NULL;
	if (i == 1)
	{
		val = ft_strdup(">>");
		type = RED_IN2;
	}
	else
		val = ft_strdup(">");
	oneuse = token_init(val, type);
	ft_lstadd_back(token, oneuse);
}

void	token_redin(token_t **token, int i)
{
	token_t *oneuse;
	char *val;
	int type;

	type = RED_IN;
	oneuse = NULL;
	if (i == 1)
	{
		val = ft_strdup("<<");
		type = RED_IN2;
	}
	else
		val = ft_strdup("<");
	oneuse = token_init(val, type);
	ft_lstadd_back(token, oneuse);
}

void	token_dollar(token_t **token, t_lexer *lexer, char **env)
{
	char *val;
	token_t *oneuse;

	lexer_step(&lexer);
	val = ft_expand(lexer, env);
	oneuse = token_init(val, DOLLAR);
	ft_lstadd_back(token, oneuse);
}

int	ft_strrchr(char *str, char c)
{
	int	i;

	i = 0;	
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}


void	token_string(token_t **token, t_lexer *lexer)
{
	char *val;
	token_t *oneuse;
	int size;
	char *str;

	str = &(lexer->src[lexer->i]);
	size = 0;
	
	while (str[size] && ft_strrchr(" \t\'\"|><$", str[size]))
		size++;
	val = malloc(sizeof(char) * size + 1);
	
	if (!val)
		return ;
	size = 0;	
	while (lexer->c && ft_strrchr(" \t\'\"|><$", lexer->c))
	{
		val[size] = lexer->c;
		lexer_step(&lexer);	
		size++;
	}
	val[size] = '\0';
	oneuse = token_init(val, STRING);
	ft_lstadd_back(token, oneuse);
}

token_t *tokenizer(t_lexer *lexer, char **env)
{
	token_t *token;
	int i;

	i = 0;
	token = NULL;
	while (lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_advance(&lexer);
		if (lexer->c == '\'')
			token_sq(&token, lexer);
		else if (lexer->c == '\"')
			token_dq(&token, lexer, env);
		else if (lexer->c == '|')
			token_pipe(&token);
		else if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
			token_redout(&token, 1);
		else if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
			token_redin(&token, 1);
		else if (lexer->c == '>')
			token_redout(&token, 0);
		else if (lexer->c == '<')
			token_redin(&token, 0);
		else if (lexer->c == '$')
			token_dollar(&token, lexer, env);	
		else
			token_string(&token, lexer);
		lexer_step(&lexer);
	}
	return (token);
}