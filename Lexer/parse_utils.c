/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 06:33:11 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 06:33:19 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parse.h"

int	what_type(t_token *token)
{
	if (token->e_type == RED_OUT || token->e_type == RED_OUT2)
		return (1);
	else
		return (0);
}

int	what_fd(t_token *token)
{
	int	fd;

	fd = -1;
	if (token->e_type == RED_OUT)
		fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (token->e_type == RED_IN)
		fd = open(token->next->value, O_RDONLY);
	else if (token->e_type == RED_OUT2)
		fd = open(token->next->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	printcmd(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd && cmd->cmd[i])
		{
			printf("%s\n", cmd->cmd[i]);
			i++;
		}
		printf("in = %d\nout = %d\nflag = %d\n", cmd->in, cmd->out, cmd->err);
		cmd = cmd->next;
	}
}

char	**to_cargs(char **cargs, char *val)
{
	if (!cargs)
	{
		cargs = (char **)s_malloc(sizeof(char *) * 2);
		*cargs = val;
		*(cargs + 1) = NULL;
	}
	else
		cargs = fillcargs(cargs, val);
	return (cargs);
}

char	**fillcargs(char **cargs, char *val)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cargs[i])
		i++;
	tmp = (char **)s_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (cargs[i])
	{
		tmp[i] = cargs[i];
		i++;
	}
	tmp[i] = val;
	tmp[i + 1] = NULL;
	return (tmp);
}
