/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:05 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/26 06:32:11 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "token.h"
#include "parse.h"
#include <string.h>


int is_error(token_t *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token->value, 2);
	else 
		ft_putstr_fd("newline", 2);	
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	check_if(token_t *next, int pipe)
{	
	if (!next)
		return (0);
	if (next->type == PIPE)
		return (0);
	else if (next->type == RED_OUT && pipe == 0)
		return (0);
	else if (next->type == RED_IN && pipe == 0)
		return (0);
	else if (next->type == RED_OUT2 && pipe == 0)
		return (0);
	else if (next->type == RED_IN2 && pipe == 0)
		return (0);
	return (1);					
}

int if_error(token_t *token)
{
	token_t *head;
	int i;
	head = token;
	i = 0;
	while (head)
	{
		if (head->type == PIPE && !check_if(head->next, 1))
			i = 1;
		else if (head->type == RED_OUT && !check_if(head->next, 0))
			i = 1;
		else if (head->type == RED_IN2 && !check_if(head->next, 0))
			i = 1;
		else if (head->type == RED_OUT2 && !check_if(head->next, 0))
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

t_cmd	*ft_parse(token_t *token, t_cmd *cmd)
{
	char **cargs;
	int in;
	int out;

	in = 0;
	out = 1;
	cargs = NULL;
	if (if_error(token))
		return (NULL);
	while (token)
	{
		if (token->err)
			return (NULL);
		else if (access_tokens(token) == 2)
			out = ft_access_cond(&token, &cargs);
		else if (access_tokens(token) == 1)
			in = ft_access_cond(&token, &cargs);	
		else if (token->type == PIPE)
			cargs = new_cmd(&cmd, &in, &out, cargs);
		else
			cargs = to_cargs(cargs, token->value);
		if (token)	
			token = token->next;
	}
	new_cmd(&cmd, &in, &out, cargs);
	return (cmd);
}