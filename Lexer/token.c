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
