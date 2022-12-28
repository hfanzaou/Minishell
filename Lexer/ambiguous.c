/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:31:59 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 07:32:08 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int 	ft_puterror(char *val)
{
	global.exit_status = 256;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(val, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (1);
}

char	*to_dollar(char *str)
{
	t_envlist	*temp;

	temp = global.envlist;
	while (temp)
	{
		if (!ft_strcmp(temp->value, str))
			return (temp->key);
		temp = temp->next;
	}
	return ("\0");
}

int 	if_ambiguous(token_t *token)
{
	int i;
	token_t *head;
	char *to_dol;

	head = token;
	i = 0;
	if (head->type == DOLLAR)
	{
		to_dol = ft_strjoin2("$", to_dollar(token->value), 1);
		if (!head->value[0])
			return (ft_puterror(to_dol));
		while (head->value[i])
		{
			if (head->value[i] == ' ' || head->value[i] == '\t')
				return (ft_puterror(to_dol));
			i++;	
		}	
	}
	return (0);
}