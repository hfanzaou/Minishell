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

void	printcmd(t_cmd *cmd)
{
	int i;
	i = 0;
	while (cmd)
	{
		while (cmd->cmd[i])
			printf("%s ", cmd->cmd[i++]);
		cmd = cmd->next;	
	}
}

t_cmd *ft_parse(token_t *token, t_cmd *cmd)
{
	int i;

	i = 0;
	while (token)
	{
		i = 0;
		if (token->type == STRING)
		{
			while (token && token->type == STRING)
			{
				cmd->cmd[i] = token->value;
				i++;
				token = token->next;
				if (!token)
					break;
			}
		}
		else if (token->type == RED_IN)
			cmd->out = open(token->value, O_RDWR);
		else if (token->type == RED_OUT)
			cmd->in = open(token->value, O_RDWR);
		else if (token->type == PIPE)
		{
			printf("here");
			cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
			cmd = cmd->next;
		}
		token = token->next;	
	}
	printcmd(cmd);
	return (cmd);
}

