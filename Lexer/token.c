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

token_t *token_init(char *va, int type)
{
	token_t *token;
	token = (token_t *)malloc(sizeof(token_t));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = va;
	token->next = NULL;		
	return (token);	
}
