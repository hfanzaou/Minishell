/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redpipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:35:39 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:35:41 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"

void	specialsymbols(t_lexer *lexer, t_token **token, int type)
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

int	what_redt(char c, char nc)
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

void	token_pipe(t_token **token)
{
	t_token	*oneuse;
	char	*val;
	int		type;

	type = PIPE;
	oneuse = NULL;
	val = ft_strdup2("|");
	oneuse = token_init(val, type, 0, 0);
	ft_lstadd_back(token, oneuse);
}

void	token_redout(t_token **token, int i)
{
	t_token	*oneuse;
	char	*val;
	int		type;

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

void	token_redin(t_lexer *lexer, t_token **token, int i)
{
	t_token	*oneuse;
	char	*val;
	int		type;
	int		j;
	int		f;

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
