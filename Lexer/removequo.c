/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:17:52 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:17:55 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*put_enqval(char *str, char c, int n)
{
	char	*val;
	int		i;

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
	int	i;
	int	f;

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
