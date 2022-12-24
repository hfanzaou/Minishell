/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:02:26 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/08 21:02:56 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"


t_lexer *ft_lexer(char *src)
{
	t_lexer *lexer;
	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->src = src;
	lexer->i = 0;
	lexer->c = src[lexer->i];
	lexer->size = strlen(src);
	return (lexer);
}

void	lexer_advance(t_lexer **lexer)
{
	if ((*lexer)->i < (*lexer)->size)
	{
		(*lexer)->i += 1;
		(*lexer)->c = (*lexer)->src[(*lexer)->i];
	}
}

void 	lexer_advance_i(t_lexer **lexer, int n)
{
	int i;

	i = 0;
	while ((*lexer)->src[(*lexer)->i + i] && i < n)
	{
		lexer_advance(lexer);
		i++;
	}
}

char 	nextcval(t_lexer *lexer, int i)
{
		return(lexer->src[lexer->i + i]);	
}