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

char	*joinex(char *line)
{
	int i;
	char *c;
	char *val;

	c = ft_strdup(" ");
	val = ft_strdup("");
	i = 0;
	while (line[i])
	{	
		c[0] = line[i];
		c[1] = '\0';
		if (line[i] == '$')
		{
			val = ft_strjoin2(val, ft_expand(&line[i], global.envp, NULL, 0), strlen(val));
			i += ft_skip(&line[i + 1]);
		}
		else
			val = ft_strjoin2(val, c, strlen(val));
		if (!line[i])
			break;
		i++;		
	}
	free(c);
	return (val);
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
			str = line;
			if (!ft_strrchr(line, '$') && here == 0)
				str = joinex(line);
			if (!ft_strrchr(line, '$') && !ft_strcmp(joinex(line), eof))
				exit(0);
			else if (ft_strcmp(str, eof))
			{
				write(fd[1], str, strlen(str));
				write(fd[1], "\n", 1);
			}
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

int		what_type(token_t *token)
{
	if (token->type == RED_OUT || token->type == RED_OUT2)
		return (1);
	else 
		return (0);	
}

int		what_fd(token_t *token)
{
	int fd;

	fd = -1;
	if (token->type == RED_OUT)
		fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (token->type == RED_IN)
		fd = open(token->next->value, O_RDONLY);
	else if (token->type == RED_OUT2)
		fd = open(token->next->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);	
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
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(to_dol, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			return (1);
		}
		while (head->value[i])
		{
			if (head->value[i] == ' ' || head->value[i] == '\t')
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(to_dol, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return (1);
			}
			i++;	
		}	
	}
	return (0);
}

int		if_access(token_t **token, char ***cargs)
{
	DIR *dir;
	int fd;
	fd = what_type(*token);
	if (if_ambiguous((*token)->next))
	{
		while ((*token)->next && (*token)->next->type != PIPE)
			*token = (*token)->next;
		*cargs = NULL;	
		return (fd);	
	}
	dir = opendir((*token)->next->value);
	if (dir)
	{
		free(dir);
		ft_error("minishell :", (*token)->next->value, ": is a directory");
		while ((*token)->next && (*token)->next->type != PIPE)
			*token = (*token)->next;
		return (fd);	
	}	
	else
		fd = what_fd(*token);
	if (access((*token)->next->value, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror((*token)->next->value);
		while ((*token)->next && (*token)->next->type != PIPE)
			*token = (*token)->next;
		*cargs = NULL;	
		return (fd);
	}
	return (fd);
}

int		ft_access_cond(token_t **token, char ***cargs)
{
	int fd;

	fd = what_type(*token);
	if ((*token)->type == RED_OUT)
		fd = if_access(token, cargs);
	else if ((*token)->type == RED_IN)
		fd = if_access(token, cargs);
	else if ((*token)->type == RED_OUT2)
		fd = if_access(token, cargs);
	else if ((*token)->type == RED_IN2)
		fd = ft_herdoc((*token)->next->value, (*token)->here);
	(*token) = (*token)->next;
	return (fd);
}

int 	access_tokens(token_t *token)
{
	if (token->type == RED_OUT)
		return (2);
	else if (token->type == RED_IN)
		return (1);
	else if (token->type == RED_OUT2)
		return (2);
	else if (token->type == RED_IN2)
		return (1);
	return (0);				
}

t_cmd	*ft_parse(token_t *token, t_cmd *cmd)
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
	oneuse = s_malloc(sizeof(t_cmd));
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
				cargs = (char **)s_malloc(sizeof(char *) * 2);
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
	ft_lstadd_backc(&cmd, oneuse);
	//cargs = NULL;
	//printcmd(cmd);
	return (cmd);
}