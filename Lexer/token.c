/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:21:48 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 08:50:54 by hfanzaou         ###   ########.fr       */
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

t_cmd	*init_cmd(char **cargs, int in, int out)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)s_malloc(sizeof(t_cmd));
	cmd->cmd = cargs;
	cmd->in = in;
	cmd->out = out;
	cmd->next = NULL;
	return (cmd);
}
