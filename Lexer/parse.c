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
#include <string.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], sizeof(char));
		i++;
	}
}

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
		printf("in = %d\nout = %d\nflag = %d\n", cmd->in, cmd->out, cmd->err);
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

int	ft_herdoc(char *eof, int here)
{
	int i;
	char *line;
	char *str;
	int fd[2];

	pipe(fd);
	i = fork();
	if (i == 0)
	{
		while ((line = readline(">")))
		{
			str = ft_strdup(line);
			if (line[0] == '$' && here == 0)
				str = ft_expand(line, global.envp, NULL, 0);
			if (ft_strcmp(str, eof))
			{
				write(fd[1], str, strlen(str));
				write(fd[1], "\n", 1);
			}
			else if (line[0] == '$' && !ft_strcmp(ft_expand(line, global.envp, NULL, 0), eof))
				exit(0);
			else if (!ft_strcmp(line, eof))
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
int is_error(token_t *token)
{
	ft_putstr_fd("MINISHELL: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token->value, 2);
	else 
		ft_putstr_fd("newline", 2);	
	ft_putstr_fd("'\n", 2);
	return (1);
}
int	check_if(int type)
{	
	if (type == PIPE)
		return (0);
	else if (type == RED_OUT)
		return (0);
	else if (type == RED_IN)
		return (0);
	else if (type == RED_OUT2)
		return (0);
	else if (type == RED_IN2)
		return (0);
	return (1);					
}

int if_error(token_t *token)
{
	token_t *head;
	int i;
	head = token;
	i = 0;
	while (head->next)
	{
		if (head->type == PIPE && !check_if(token->next->type))
			i = 1;
		else if (head->type == RED_OUT && !check_if(token->next->type))
			i = 1;
		else if (head->type == RED_IN2 && !check_if(token->next->type))
			i = 1;
		else if (head->type == RED_OUT2 && !check_if(token->next->type))
			i = 1;
		if (i == 1)
			return (is_error(token->next));
		head = head->next;					
	}
	return (0);
}
t_cmd *ft_parse(token_t *token, t_cmd *cmd)
{
	t_cmd *oneuse;
	char **cargs;
	int in;
	int out;
	int flag;

	in = 0;
	out = 1;
	flag = 0;
	cargs = NULL;
	oneuse = malloc(sizeof(t_cmd));
	if (if_error(token))
		return (NULL);
	while (token)
	{
		if (token->err)
			return (NULL);
		else if (token->type == RED_OUT)
		{
			token = token->next;
			out = open(token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (access(token->value, W_OK) != 0)
			{
				ft_putstr_fd("MINISHELL: ", 2);
				perror(token->value);
				while (token->next && token->next->type != PIPE)
					token = token->next;
			}
		}
		else if (token->type == RED_IN)
		{
			token = token->next;
			in = open(token->value, O_RDONLY);
			if (access(token->value, W_OK) != 0)
			{
				ft_putstr_fd("MINISHELL: ", 2);
				perror(token->value);
				while (token->next && token->next->type != PIPE)
					token = token->next;
			}
		}
		else if (token->type == RED_OUT2)
		{
			token = token->next;
			out = open(token->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (access(token->value, W_OK) != 0)
			{
				ft_putstr_fd("MINISHELL: ", 2);
				perror(token->value);
				while (token->next && token->next->type != PIPE)
					token = token->next;
			}
		}
		else if (token->type == RED_IN2)
		{
			token = token->next;
			in = ft_herdoc(token->value, token->here);	
			if (access(token->value, W_OK) != 0)
			{
				ft_putstr_fd("MINISHELL: ", 2);
				perror(token->value);
				while (token->next && token->next->type != PIPE)
					token = token->next;
			}
		}
		else if (token->type == PIPE)
		{
			oneuse = init_cmd(cargs, in, out, flag);
			ft_lstadd_backc(&cmd, oneuse);
			cargs = NULL;
			in = 0;
			out = 1;
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
	oneuse = init_cmd(cargs, in, out, flag);
	//free(cargs);
	//cargs = NULL;
	ft_lstadd_backc(&cmd, oneuse);
	//cargs = NULL;
	//printcmd(cmd);
	return (cmd);
}