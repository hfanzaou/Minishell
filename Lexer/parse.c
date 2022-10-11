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

t_cmd *ft_parse(token_t *token, t_cmd *cmd)
{
	int i;
	t_cmd *oneuse;
	char **cargs;

	i = 0;
	while (token)
	{
		if (token->type == STRING)
		{
			i = 0;
			while (token && token->type == STRING)
			{
				cargs = (char **)realloc(cmd->cmd, sizeof(char *) * (i + 2));
				cargs[i] = token->value;
				i++;
				cargs = NULL;
				if (token->next && token->next->type != STRING)
					break ;
				token = token->next;
			}
		}
		else if (token->type == RED_IN)
			cmd->out = open(token->next->value, O_CREAT, O_RDWR);
		else if (token->type == RED_OUT)
			cmd->in = open(token->next->value, O_CREAT, O_RDWR);
		else if (token->type == PIPE)
		{
			cmd->next = NULL;
			cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
			cmd = cmd->next;
		}
		if (!token && token->next->type = PIPE)
		{
			cmd->next = NULL;
			break;
		}
		token = token->next;	
	}
	//printcmd(cmd);
	return (cmd);
}

