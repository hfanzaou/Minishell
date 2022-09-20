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

t_lexer *lexer(char *src)
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

void	lexer_step(t_lexer **lexer)
{
	if ((*lexer)->i < (*lexer)->size)
	{
		(*lexer)->i += 1;
		(*lexer)->c = (*lexer)->src[(*lexer)->i];
	}
}

t_lexer *lexer_ntoken(t_lexer *lexer)
{
	while (lexer->c)
	{
		if (isalpha(lexer->c))
			lexer_step(&lexer);	
	}
	return (NULL);
}