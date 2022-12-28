/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:25:05 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:25:08 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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
		&& ft_isalnum(lexer->src[lexer->i + 2]))
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
			val = ft_strjoin2(val, to_join(str[i]), ft_strlen(val));
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
