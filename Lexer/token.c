/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:21:48 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/12 01:21:52 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

token_t *token_init(char *va, int type, int flag, int here)
{
	token_t *token;
	token = (token_t *)s_malloc(sizeof(token_t));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = va;
	token->next = NULL;
	token->err = flag;
	token->here = here;
	return (token);	
}

char	*ft_realloc(char *str, int j)
{
	char	*t;
	int		i;

	i = 0;
	t = s_malloc(sizeof(char) * j);
	if (!t)
		return (NULL);
	while (str[i])
	{
		t[i] = str[i];
		i++;
	}
	t[i] = str[i];
	// free(str);
	str = s_malloc(sizeof(char) * j + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (t[i])
	{
		str[i] = t[i];
		i++;
	}
	// free(t);
	return (str);
}
