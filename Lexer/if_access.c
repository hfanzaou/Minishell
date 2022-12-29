/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:07:44 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 03:20:54 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	access_errors(t_token **token, char	***cargs, int f)
{
	int	fd;

	fd = what_type(*token);
	g_global.exit_status = 256;
	while ((*token)->next && (*token)->next->e_type != PIPE)
		*token = (*token)->next;
	if (f)
		*cargs = NULL;
	return (fd);
}

int	if_access(t_token **token, char ***cargs)
{
	DIR	*dir;
	int	fd;

	fd = what_type(*token);
	if (if_ambiguous((*token)->next))
		return (access_errors(token, cargs, 1));
	dir = opendir((*token)->next->value);
	if (dir)
	{
		free(dir);
		ft_error("minishell :", (*token)->next->value, ": is a directory");
		return (access_errors(token, cargs, 0));
	}
	else
		fd = what_fd(*token);
	if (access((*token)->next->value, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror((*token)->next->value);
		return (access_errors(token, cargs, 1));
	}
	return (fd);
}

int	ft_access_cond(t_token **token, char ***cargs)
{
	int	fd;

	fd = what_type(*token);
	if ((*token)->e_type == RED_OUT)
		fd = if_access(token, cargs);
	else if ((*token)->e_type == RED_IN)
		fd = if_access(token, cargs);
	else if ((*token)->e_type == RED_OUT2)
		fd = if_access(token, cargs);
	else if ((*token)->e_type == RED_IN2)
		fd = ft_herdoc((*token)->next->value, (*token)->here);
	if ((*token))
		(*token) = (*token)->next;
	return (fd);
}

int	access_tokens(t_token *token)
{
	if (token->e_type == RED_OUT)
		return (2);
	else if (token->e_type == RED_IN)
		return (1);
	else if (token->e_type == RED_OUT2)
		return (2);
	else if (token->e_type == RED_IN2)
		return (1);
	return (0);
}
