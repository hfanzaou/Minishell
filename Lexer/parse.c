/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:05 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/26 17:06:07 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
# include "token.h"
#include <string.h>

void	printcmd(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			printf("%s\n", cmd->cmd[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

int ft_cmdsize(token_t *token)
{
	int i;
	i = 0;
	token_t *tmp;

	tmp = token;
	while (tmp && tmp->type == STRING)
	{	
		i++;
		tmp = tmp->next;
	}
	return (i);	
}

t_cmd	*ft_lstlastc(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	ft_lstadd_backc(t_cmd **lst, t_cmd *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlastc(*lst)->next = new;
}

t_cmd *ft_parse(token_t *token, t_cmd *cmd)
{
	t_cmd *oneuse;
	char **cargs;
	int in;
	int out;

	in = 0;
	out = 1;
	oneuse = malloc(sizeof(t_cmd));
	while (token)
	{
		if (token->type == STRING)
		{
			cargs = (char **)malloc(sizeof(char *) * 3);
			*cargs = token->value;
			*(cargs + 1) = NULL;
		}
		else if (token->next && token->type == RED_IN)
		{
			//printf("here 2\n");
			token = token->next;
			out = open(token->value, O_CREAT, O_RDWR);
		}
		else if (token->next && token->type == RED_OUT)
		{
			//printf("here 3\n");
			token = token->next;
			in = open(token->value, O_CREAT, O_RDWR);
		}
		else if (token->type == PIPE)
		{
			oneuse = init_cmd(cargs, in, out);
			ft_lstadd_backc(&cmd, oneuse);
		}
		if (!token)
			break;
		token = token->next;	
	}
	//printf("here 4\n");
	oneuse = init_cmd(cargs, in, out);
	ft_lstadd_backc(&cmd, oneuse);
	printcmd(cmd);
	return (cmd);
}

