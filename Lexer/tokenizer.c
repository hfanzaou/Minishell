/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:17:24 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/21 17:02:44 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	int_len(unsigned int nu)
{
	int	i;

	i = 1;
	while (nu > 9)
	{
		nu = nu / 10;
		i++;
	}
	return (i);
}

char	*assign(char *str, unsigned int n, int sign)
{
	int	i;

	i = int_len(n) + sign - 1;
	if (sign)
		*str = '-';
	while (n > 9)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	str[i] = n + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nu;
	char			*res;
	int				sign;
	int				len;

	sign = 0;
	if (n < 0)
	{
		nu = n * -1;
		sign = 1;
	}
	else
		nu = n;
	len = int_len(nu);
	res = malloc((len + 1 + sign) * sizeof(char));
	if (!res)
		return (NULL);
	res[len + sign] = '\0';
	return (assign(res, nu, sign));
}

char	*ft_strjoin(char const *s1, char const *s2, int n)
{
	int		i;
	int		j;
	char	*c;

	if (!s1 || !s2)
		return (0);
	i = strlen((char *)s1) + strlen((char *)s2);
	c = malloc(sizeof(char) * i + 1);
	if (c == NULL)
		return (0);
	j = 0;
	while (s1[j] && n)
	{
		c[j] = s1[j];
		n--;
		j++;
	}
	n = 0;
	while (s2[n])
	{
		c[j] = s2[n];
		n++;
		j++;
	}
	c[j] = '\0';
	return (c);
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
			return (1);
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

char	*remove_quotes(char c, t_lexer *lexer, char *str)
{
	int i;
	int f;
	int e;
	char *val;

	i = 0;
	f = 0;
	e = 0;
	while (lexer->c && lexer->c != c)
	{
		i++;
		lexer_advance(&lexer);
	}
	while (lexer->c && lexer->c == c)
	{
		f++;
		lexer_advance(&lexer);
	}
	if (!lexer->c)
		e = f;
	while (lexer->c && lexer->c != c)
	{
		i++;
		lexer_advance(&lexer);
	}
	while (lexer->c && lexer->c == c && e < f)
	{
		e++;
		lexer_advance(&lexer);
	}
	if (f - e != 0)
		return (NULL);
	val = malloc(sizeof(char) * i + 1);
	i = 0;
	f = 0;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		val[f] = str[i];
		f++;
		i++;		
	}
	val[f] = '\0';
	return (val);	
}

char	*ft_expand(char *val, char **env, t_lexer **lexer, int j)
{
	char *s;
	int i;
	int l;

	l = 1;
	s = val;
	if (!s)
		return NULL;
	if (s[1] == '?')
	{
		lexer_advance(lexer);
		return (ft_strdup(ft_itoa(global.exit_status)));
	}
	while (s[l] && (isalpha(s[l]) || s[l] == '_'))
	{
		if (j == 1)
			lexer_advance(lexer);
		l++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_memcmp(env[i], &s[1], l - 1))
			return (ft_strdup(&env[i][l]));
			//return (ft_strjoin(&env[i][l], &s[l], strlen(&env[i][l])));
		i++;
	}
	return (ft_strdup("\0"));
}

int 	ft_skip(char *str)
{
	int i;

	i = 0;
	while (str[i] && (isalpha(str[i]) || str[i] == '_'))
		i++;
	return (i);	
}

int 	howmuchq(t_lexer *lexer)
{
	int i;

	i = 0;
	while (lexer->src[lexer->i + i] == '\'')
		i++;
	return (i);	
}

void	token_sq(token_t **token, t_lexer *lexer)
{	
	token_t *oneuse;
	char *val;
	int i;
	char *str;
	char *c;
	int j;
	j = 0;
	if (howmuchq(lexer) % 2 == 0)
		j = 1;
	str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
	if (!str)
	 	return ;
	c = malloc(sizeof(char) * 2);
	c[0] = '\'';
	c[1] = '\0';
	str = ft_strjoin(str, c, strlen(str));
	while (lexer->c && ft_strrchr(" \t|><", lexer->c))
	{
		c[0] = lexer->c;
		c[1] = '\0';
		str = ft_strjoin(str, c, strlen(str));
		lexer_advance(&lexer);
	}
	i = 0;
	val = ft_strdup("");
	while (str[i])
	{
		c[0] = str[i];
		c[1] = '\0';
		if (j == 1 && str[i] == '$' && (isalpha(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
		{
			val = ft_strjoin(val, ft_expand(&str[i], global.envp, &lexer, 0), i);
			i += ft_skip(&str[i + 1]);
		}
		else if (str[i] != '\'')
			val = ft_strjoin(val, c, strlen(val));
		i++;
	}	
	oneuse = token_init(val, SINGLE_Q);
	ft_lstadd_back(token, oneuse);
}

void	token_dq(token_t **token, t_lexer *lexer, char **env)
{	
	token_t *oneuse;
	char *val;
	int i;
	char *str;
	char *c;

	str = ft_strdup("");
	while (lexer->c && ft_strrchr(" \t", lexer->c))
	{
		if (lexer->c == '\"')
			str = ft_strjoin(str, remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]), strlen(str));
		else 
			break;		
	}
	if (!str)
	 	return ;
	c = malloc(sizeof(char) * 2);
	c[0] = '\"';
	c[1] = '\0';
	str = ft_strjoin(str, c, strlen(str));
	while (lexer->c && ft_strrchr(" \t|><", lexer->c))
	{
		c[0] = lexer->c;
		c[1] = '\0';
		str = ft_strjoin(str, c, strlen(str));
		lexer_advance(&lexer);
	}
	//printf("%s\n", str);
	(void)env;
	i = 0;
	val = ft_strdup("\0");
	while (str[i])
	{
		c[0] = str[i];
		c[1] = '\0';
		if (str[i] == '$' && (isalpha(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
		{
			val = ft_strjoin(val, ft_expand(&str[i], env, &lexer, 0), strlen(val));
			i += ft_skip(&str[i + 1]);
		}
		else if (str[i] != '\"')
			val = ft_strjoin(val, c, strlen(val));
		i++;
	}
	free(c);
	free(str);
	oneuse = token_init(val, DOUBLE_Q);
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

	type = RED_OUT;
	oneuse = NULL;
	if (i == 1)
	{
		val = ft_strdup(">>");
		type = RED_OUT2;
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

char 	*string(t_lexer *lexer)
{
	char *val;
	char *c;
	int i;

	c = malloc(sizeof(char) * 2);
	i = 0;
	while (lexer->c && ft_strrchr(" \t|><$\"\'", lexer->c))
	{
		c[0] = lexer->c;
		c[1] = '\0';
		if (i == 0)
			val = ft_strdup(c);
		else
			val = ft_strjoin(val, c, strlen(val));
		i++;
		lexer_advance(&lexer);
	}
	return (val);
}

void	token_dollar(token_t **token, t_lexer *lexer)
{
	char *val;
	char *str;
	token_t *oneuse;
	int i;
	char *c;
	i = 0;
	val = ft_strdup("");
	while (lexer->c && ft_strrchr(" \t", lexer->c))
	{
		if (lexer->c == '$' && (isalpha(nextcval(lexer, 1)) || !ft_strrchr("?_", nextcval(lexer, 1))))
		{
			str = ft_expand(&lexer->src[lexer->i], global.envp, &lexer, 1);
			val = ft_strjoin(val, str, strlen(val));
			lexer_advance(&lexer);
		}
		else if (lexer->c == '\"')
		{
			str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
			if (!str)
				return ;
			c = malloc(sizeof(char) * 2);
			c[0] = '\"';
			c[1] = '\0';
			str = ft_strjoin(str, c, strlen(str));
			while (lexer->c && ft_strrchr(" \t|><", lexer->c))
			{
				c[0] = lexer->c;
				c[1] = '\0';
				str = ft_strjoin(str, c, strlen(str));
				lexer_advance(&lexer);
			}
			i = 0;
			while (str[i])
			{
				c[0] = str[i];
				c[1] = '\0';
				if (str[i] == '$' && (isalpha(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
				{
					val = ft_strjoin(val, ft_expand(&str[i], global.envp, &lexer, 0), i);
					i += ft_skip(&str[i + 1]);
				}	
				else if (str[i] != '\"')
					val = ft_strjoin(val, c, strlen(val));
				i++;
			}
		}
		else if (lexer->c == '\'')
		{
			str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
			val = ft_strjoin(val, str, strlen(val));
		}
		else if (lexer->c == '$' && (ft_strrchr(" \t", lexer->c) || !lexer->src[lexer->i + i]))
		{
			val = ft_strjoin(val, "$", strlen(val));
			lexer_advance(&lexer);
		}
		else if (lexer->c == '$')
			lexer_advance(&lexer);
		else
		{
			str = string(lexer);
			if (!val)
				val = ft_strjoin("\0", str, 0);
			else
				val = ft_strjoin(val, str, strlen(val));
		}
	}	
	oneuse = token_init(val, DOLLAR);
	ft_lstadd_back(token, oneuse);
}

void	token_string(token_t **token, t_lexer *lexer, char **env)
{
	char *val;
	token_t *oneuse;
	int i;
	char *str;
	char *c;

	i = 0;
	val = ft_strdup("");
	while (lexer->c && ft_strrchr(" \t", lexer->c))
	{
	 	if (lexer->c == '$' && (isalpha(nextcval(lexer, 1)) || !ft_strrchr("?_", nextcval(lexer, 1))))
		{
			str = ft_expand(&lexer->src[lexer->i], env, &lexer, 1);
			val = ft_strjoin(val, str, strlen(val));
			lexer_advance(&lexer);
			free(str);
		}
		else if (lexer->c == '\"')
		{
			str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
			if (!str)
				return ;
			c = malloc(sizeof(char) * 2);
			c[0] = '\"';
			c[1] = '\0';
			str = ft_strjoin(str, c, strlen(str));
			while (lexer->c && ft_strrchr(" \t|><", lexer->c))
			{
				c[0] = lexer->c;
				c[1] = '\0';
				str = ft_strjoin(str, c, strlen(str));
				lexer_advance(&lexer);
			}
			i = 0;
			while (str[i])
			{
				c[0] = str[i];
				c[1] = '\0';
				if (str[i] == '$' && (isalpha(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
				{
					val = ft_strjoin(val, ft_expand(&str[i], env, &lexer, 0), strlen(val));
					i += ft_skip(&str[i + 1]);
				}	
				else if (str[i] != '\"')
					val = ft_strjoin(val, c, strlen(val));
				i++;
			}			
		}
		else if (lexer->c == '\'')
		{
			str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
			val = ft_strjoin(val, str, strlen(val));
			free(str);
		}
		else if (lexer->c == '$' && (ft_strrchr(" \t", lexer->c) || !lexer->src[lexer->i + i]))
		{
			val = ft_strjoin(val, "$", strlen(val));
			lexer_advance(&lexer);
		}
		else if (lexer->c == '$')
			lexer_advance(&lexer);
		else
		{
			str = string(lexer);
			if (!val)
				val = ft_strdup(str);
			else
				val = ft_strjoin(val, str, strlen(val));		
		}
	}
	oneuse = token_init(val, STRING);
	ft_lstadd_back(token, oneuse);
}

void	token_exit_status(token_t **token, t_lexer *lexer)
{
	char *val;
	token_t *oneuse;
	lexer_advance_i(&lexer, 1);
	val = ft_itoa(global.exit_status);
	oneuse = token_init(val, EXIT);
	ft_lstadd_back(token, oneuse);
}

token_t *tokenizer(t_lexer *lexer)
{
	token_t *token;

	token = NULL;
	while (lexer->c)
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_advance(&lexer);
		else if (lexer->c == '\'')
			token_sq(&token, lexer);
		else if (lexer->c == '\"')
		{	
			token_dq(&token, lexer, global.envp);
			//printf("%s\n", token->value);
		}
		else if (lexer->c == '|')
		{
			lexer_advance(&lexer);
			token_pipe(&token);
		}
		else if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
		{
			lexer_advance(&lexer);
			token_redout(&token, 1);
		}
		else if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
		{
			lexer_advance(&lexer);
			token_redin(&token, 1);
		}
		else if (lexer->c == '>')
		{
			lexer_advance(&lexer);
			token_redout(&token, 0);
		}
		else if (lexer->c == '<')
		{
			lexer_advance(&lexer);
			token_redin(&token, 0);
		}
		else if (lexer->c == '$')
			token_dollar(&token, lexer);
		else
			token_string(&token, lexer, global.envp);
		if (lexer->i == lexer->size)
			break ;	
		if (lexer->c == ' ' && lexer->c == '\t')
			lexer_advance(&lexer);
	}
	//printf_token(token);
	return (token);
}