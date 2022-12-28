/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 02:17:24 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/26 06:32:35 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"


void printf_token(token_t *token)
{
	printf("In token\n");
	while (token)
	{
		printf("type  = %d\n", token->type);
		printf("value = %s\n", token->value);
		printf("flag = %d\n", token->err);
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

/*int ft_size(t_lexer *lexer)
{
	int i;

	i = 0;
	while (lexer->src[lexer->i + i] && (lexer->src[lexer->i + i] != '\'' 
		|| lexer->src[lexer->i + i] != '\"'))
		i++;	
	if (!lexer->src[i])
		return (-1);
	return (i);	
}*/

char	*put_enqval(char *str, char c, int n)
{
	char *val;
	int i;

	i = 0;
	val = s_malloc(sizeof(char) * (n + 1));
	if (!val)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		val[i] = str[i];
		i++;
	}
	val[i] = '\0';
	return (val);
}

char	*remove_quotes(char c, t_lexer *lexer, char *str)
{
	int i;
	int f;

	i = 0;
	f = 0;
	if (lexer->c == c && lexer->src[lexer->i + 1] == c)
	{
		lexer_advance(&lexer);
		lexer_advance(&lexer);
		return ("\0");
	}
	else 
		lexer_advance(&lexer);
	while (lexer->c && lexer->c != c)
	{
		i++;
		lexer_advance(&lexer);
	}
	if (!lexer->c)
	{
		ft_putstr_fd("minishell : syntax error unclosed quotes\n", 2);
		return (NULL);
	}
	lexer_advance(&lexer);
	return (put_enqval(&str[1], c, i));	
}


char 	*to_join(char c)
{
	char *str;

	str = ft_strdup2(" ");
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char 	*dq_case(t_lexer *lexer, char **env)
{
	char *str;
	char *val;
	int i;

	i = 0;
	str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
	if (!str)
		return(NULL);
	val = ft_strdup2("");
	while (str[i])
	{
		if (str[i] == '$' && (isalnum(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
		{
			val = ft_strjoin2(val, ft_expand(&str[i], env, &lexer, 2), strlen(val));
			i += ft_skip(&str[i + 1]);
		}
		else
			val = ft_strjoin2(val, to_join(str[i]), strlen(val));
		i++;
	}
	// if (str[0])
	// 	free(str);
	// else 
	// {
	// 	// free(val);
	// 	return ("\0");
	// }
	return (val);
}

 char	*join_expand(t_lexer *lexer, char *val, char *val2, char **env)
 {
	char *str;

	str = ft_expand(val2, env, &lexer, 1);
	lexer_advance(&lexer);
	str = ft_strjoin2(val, str, strlen(val));
	return (str);
 }

 char	*just_join(t_lexer *lexer, char *val, char *c)
 {
	char *str;

	if (c[0])
	{
		str = ft_strjoin2(val, c, strlen(val));
		// free(c);
		lexer_advance(&lexer);
	}
	else if (!c[0] && lexer->c == '\"')
	{
		str = dq_case(lexer, global.envp);
		str = ft_strjoin2(val, str, strlen(val));
	}
	else 
	{
		str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
		str = ft_strjoin2(val, str, strlen(val));
	}
	if (!str)
		return (NULL);
	return (str);
 }

char 	*cond(t_lexer *lexer, char *val, char **env)
{
	char *str;

	str = NULL;
	if (lexer->c == '$' && (isalnum(nextcval(lexer, 1)) || !ft_strrchr("?_", nextcval(lexer, 1))))
		str = join_expand(lexer, val, &lexer->src[lexer->i], env);
	else if (lexer->c == '$' && (ft_strrchr(" \t", nextcval(lexer, 1)) || lexer->src[lexer->i + 1]))
		str = just_join(lexer, val, "$");
	else if (lexer->c == '$')
		lexer_advance(&lexer);
	else if (lexer->c == '\"')
		str = just_join(lexer, val, "");
	else if (lexer->c == '\'')
		str = just_join(lexer, val, "");
	else
		str = just_join(lexer, val, to_join(lexer->c));
	// if (val)
	// 	free(val);	
	if (!str)
		return (NULL);		
	return (str);
}

void	token_3(token_t **token, t_lexer *lexer, char **env, int type)
{	
	token_t *oneuse;
	char *val;

	val = ft_strdup2("");
	while (lexer->c && ft_strrchr(" \t|><", lexer->c))
	{
		val = cond(lexer, val, env);
		if (!val)
		{
			oneuse = token_init(val, type, 1, 0);
			ft_lstadd_back(token, oneuse);
			return ;
		}
	}
	oneuse = token_init(val, type, 0, 0);
	ft_lstadd_back(token, oneuse);
}

void	token_pipe(token_t **token)
{
	token_t *oneuse;
	char *val;
	int type;

	type = PIPE;
	oneuse = NULL;
	val = ft_strdup2("|");
	oneuse = token_init(val, type, 0, 0);
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
		val = ft_strdup2(">>");
		type = RED_OUT2;
	}
	else
		val = ft_strdup2(">");	
	oneuse = token_init(val, type, 0, 0);
	ft_lstadd_back(token, oneuse);
}

void	token_redin(t_lexer *lexer, token_t **token, int i)
{
	token_t *oneuse;
	char *val;
	int type;
	int j;
	int f;

	f = 0;
	j = 0;
	type = RED_IN;
	oneuse = NULL;
	if (i == 1)
	{
		val = ft_strdup2("<<");
		while (lexer->src[lexer->i + j] && lexer->src[lexer->i + j] != '\'' 
				&& lexer->src[lexer->i + j] != '\"')
			j++;
		if ((lexer->src[lexer->i + j] && (lexer->src[lexer->i + j] == '\'' 
				|| lexer->src[lexer->i + j] == '\"')))
			f = 1;
		type = RED_IN2;
	}
	else
		val = ft_strdup2("<");
	oneuse = token_init(val, type, 0, f);
	ft_lstadd_back(token, oneuse);
}

int 	if_pipe(t_lexer *lexer)
{
	int i;
	
	i = 1;
	while (lexer->i - i >= 0 && !ft_strrchr(" \t", lexer->src[lexer->i - i]))
		i--;
	if (lexer->src[lexer->i - i] == '|')
		return (1);
	return (0);	
}

int		executedollar(t_lexer *lexer)
{
	int i;

	if (lexer->i && !if_pipe(lexer))
		return (0);
	i = 1;
	if (lexer->src[lexer->i + i] == '_' 
		&& isalnum(lexer->src[lexer->i + 2]))
		i++;
	while (lexer->src[lexer->i + i] 
		&& ft_strrchr(" \t|><", lexer->src[lexer->i + i]))
		i++;
	if (!lexer->src[lexer->i + i] 
		|| !ft_strrchr(" \t", lexer->src[lexer->i + i]))
		return (1);
	return (0);		
}

char	*expand_exdollarp2(token_t **token, char *str)
{
	char *val;
	int i;
	token_t *oneuse;

	i = 0;
	val = ft_strdup2("");
	while (str[i])
	{	
		if (ft_strrchr(" \t", str[i]))
			val = ft_strjoin2(val, to_join(str[i]), strlen(val));
		else if (val[0] && !ft_strrchr(" \t", str[i]) 
			&& str[i + 1] && ft_strrchr(" \t", str[i + 1]))
		{
			oneuse = token_init(val, EXDOLLAR, 0, 0);
			ft_lstadd_back(token, oneuse);
			val = ft_strdup2("");
		}
		i++;
	}
	return (val);
}

void	expand_exdollar(token_t **token, t_lexer *lexer, char **env)
{	
	char *str;
	char *val;
	token_t *oneuse;

	str = ft_expand(&lexer->src[lexer->i], env, &lexer, 1);
	lexer_advance(&lexer);
	val = expand_exdollarp2(token, str);
	if (val[0])
	{
		oneuse = token_init(val, EXDOLLAR, 0, 0);
		ft_lstadd_back(token, oneuse);
	}
}


void	passtoken_3(token_t **token, t_lexer *lexer, char **env, char c)
{
	if (c == '$')
		token_3(token, lexer, env, DOLLAR);
	else if (c == '\'')
		token_3(token, lexer, env, SINGLE_Q);
	else if (c == '\"')
		token_3(token, lexer, env, DOUBLE_Q);
	else 
		token_3(token, lexer, env, STRING);
}

void	specialsymbols(t_lexer *lexer, token_t **token, int type)
{
	lexer_advance(&lexer);
	if (type == PIPE)
		token_pipe(token);
	else if (type == RED_OUT2)
	{
		lexer_advance(&lexer);
		token_redout(token, 1);
	}
	else if (type == RED_IN2)
	{
		lexer_advance(&lexer);
		token_redin(lexer, token, 1);
	}
	else if (type == RED_OUT)
		token_redout(token, 0);
	else if (type == RED_IN)
		token_redin(lexer, token, 0);	
}

int 	what_redt(char c, char nc)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>' && nc == '>')
		return (RED_OUT2);
	else if (c == '<' && nc == '<')
		return (RED_IN2);
	else if (c == '>')
		return (RED_OUT);
	else if (c == '<')
		return (RED_IN);
	return (0);				
}

token_t *tokenizer(t_lexer *lexer)
{
	token_t *token;
	char c;
	char nc;

	token = NULL;
	while (lexer->c)
	{
		c = lexer->c;
		nc = lexer->src[lexer->i + 1];
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_advance(&lexer);
		else if (lexer->c == '$' && executedollar(lexer))
			expand_exdollar(&token, lexer, global.envp);
		else if (what_redt(c, nc))
			specialsymbols(lexer, &token, what_redt(c, nc));
		else if (lexer->c || lexer->c == '$' || lexer->c == '\'' || lexer->c == '\"')
			passtoken_3(&token, lexer, global.envp, lexer->c);
		if (lexer->i == lexer->size)
			break ;	
		else if (!lexer->c)
			return (NULL);	
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_advance(&lexer);	
	}
	return (token);
}