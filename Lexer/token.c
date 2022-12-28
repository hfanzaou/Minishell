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

t_token	*token_init(char *va, int type, int flag, int here)
{
	t_token	*token;

	token = (t_token *)s_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = va;
	token->next = NULL;
	token->err = flag;
	token->here = here;
	return (token);
}
