/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:05 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 03:24:26 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token->value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	check_if(t_token *next, int pipe)
{	
	if (!next)
		return (0);
	if (next->e_type == PIPE)
		return (0);
	else if (next->e_type == RED_OUT && pipe == 0)
		return (0);
	else if (next->e_type == RED_IN && pipe == 0)
		return (0);
	else if (next->e_type == RED_OUT2 && pipe == 0)
		return (0);
	else if (next->e_type == RED_IN2 && pipe == 0)
		return (0);
	return (1);
}

int	if_error(t_token *token)
{
	t_token	*head;
	int		i;

	head = token;
	i = 0;
	while (head)
	{
		if (head->e_type == PIPE && !check_if(head->next, 1))
			i = 1;
		else if (head->e_type == RED_OUT && !check_if(head->next, 0))
			i = 1;
		else if (head->e_type == RED_IN2 && !check_if(head->next, 0))
			i = 1;
		else if (head->e_type == RED_OUT2 && !check_if(head->next, 0))
			i = 1;
		if (i == 1)
			return (is_error(head->next));
		head = head->next;
	}
	return (0);
}

char	**new_cmd(t_cmd **cmd, int *in, int *out, char **cargs)
{
	t_cmd	*oneuse;

	oneuse = init_cmd(cargs, *in, *out, 0);
	ft_lstadd_backc(cmd, oneuse);
	*in = 0;
	*out = 1;
	return (NULL);
}

t_cmd	*ft_parse(t_token *token, t_cmd *cmd)
{
	t_cmd	tmp;

	tmp = *init_cmd(NULL, 0, 1, 0);
	printcmd(&tmp);
	if (if_error(token))
		return (NULL);
	while (token)
	{
		if (token->err)
			return (NULL);
		else if (access_tokens(token) == 2)
			tmp.out = ft_access_cond(&token, &tmp.cmd);
		else if (access_tokens(token) == 1)
			tmp.in = ft_access_cond(&token, &tmp.cmd);
		else if (token->e_type == PIPE)
			tmp.cmd = new_cmd(&cmd, &tmp.in, &tmp.out, tmp.cmd);
		else
			tmp.cmd = to_cargs(tmp.cmd, token->value);
		if (token)
			token = token->next;
		if (tmp.in == -2)
			return (NULL);
	}
	new_cmd(&cmd, &tmp.in, &tmp.out, tmp.cmd);
	return (cmd);
}
