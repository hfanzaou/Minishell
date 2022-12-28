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


char 	*cond(t_lexer *lexer, char *val, char **env)
{
	char *str;

	str = NULL;
	if (lexer->c == '$' && (ft_isalnum(nextcval(lexer, 1)) || !ft_strrchr("?_", nextcval(lexer, 1))))
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