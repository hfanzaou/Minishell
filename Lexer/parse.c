/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:05 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/15 20:37:15 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("in = %d\nout = %d\n", cmd->in, cmd->out);
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

char **fillcargs(char **cargs, char *val)
{
	char **tmp;
	int i;
	i = 0;
	while (cargs[i])
		i++;		
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
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

int	ft_herdoc(char *eof)
{
	int i;
	char *line;
	int fd[2];

	pipe(fd);
	i = fork();
	if (i == 0)
	{
		while ((line = readline(">")))
		{
			if (memcmp(line, eof, strlen(eof)))
				write(fd[1], line, strlen(line));
			else if (!memcmp(line, eof, strlen(eof)))
				exit(0);
		}
	}
	else 
	{
		wait(&i);
		close(fd[1]);
	}

	return (fd[0]);	
}

t_cmd *ft_parse(token_t *token, t_cmd *cmd)
{
	t_cmd *oneuse;
	char **cargs;
	int in;
	int out;

	in = 0;
	out = 1;
	cargs = NULL;
	oneuse = malloc(sizeof(t_cmd));
	while (token)
	{
		if (token->next && token->type == RED_OUT)
		{
			token = token->next;
			out = open(token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (token->next && token->type == RED_IN)
		{
			token = token->next;
			if (cargs)
			{
				in = open(*cargs, O_RDONLY);
				*cargs = token->value;
			}
			else 
				in = open(token->value, O_RDONLY);
			if (in < 0)
				return NULL;		
		}
		else if (token->next && token->type == RED_OUT2)
		{
			token = token->next;
			out = open(token->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (token->next && token->type == RED_IN2)
		{
			in = ft_herdoc(token->next->value);
			token = token->next;
		}
		else if (token->type == PIPE)
		{
			oneuse = init_cmd(cargs, in, out);
			ft_lstadd_backc(&cmd, oneuse);
			cargs = NULL;
		}
		else
		{
			if (!cargs)
			{
				cargs = (char **)malloc(sizeof(char *) * 2);
				*cargs = token->value;
				*(cargs + 1) = NULL;
			}
			else
				cargs = fillcargs(cargs, token->value);
		}
		if (!token)
			break;
		token = token->next;
	}
	oneuse = init_cmd(cargs, in, out);
	//free(cargs);
	//cargs = NULL;
	ft_lstadd_backc(&cmd, oneuse);
	//cargs = NULL;
	//printcmd(cmd);
	return (cmd);
}