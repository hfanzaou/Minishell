/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:49:46 by ajana             #+#    #+#             */
/*   Updated: 2022/12/13 13:35:20 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global global;

void	ft_free(char **str)
{
	while (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	print_cmdlst(t_cmd *cmd_lst)
{
	int	i = 0;

	while (cmd_lst)
	{
		while (cmd_lst->cmd[i])
			printf("%s\n", (cmd_lst->cmd)[i++]);
		cmd_lst = cmd_lst->next;
	}
}

int	cmd_count(t_cmd *cmd_lst)
{
	int count;

	count = 0;
	while (cmd_lst)
	{
		cmd_lst = cmd_lst->next;
		count++;
	}
	return (count);
}

int ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_search(char **haystack, char *needle)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (!ft_strncmp(haystack[i], needle, ft_strlen(needle)))
			return (i + 1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	char	*builtins;
	int		i;

	builtins = "echo cd pwd export unset env exit";
	if ((i = str_search(ft_split(builtins, ' '), cmd)))
		return (i);
	return (0);
}

void	excute_builtin(t_cmd *cmd_lst, int ind)
{
	if (ind == e_echo)
		echo(cmd_lst);
	else if (ind == e_cd)
		cd(cmd_lst);
	else if (ind == e_pwd)
		pwd(cmd_lst);
	else if (ind == e_export)
		export(cmd_lst);
	else if (ind == e_unset)
		unset(cmd_lst);
	else if (ind == e_env)
		env(cmd_lst);
	// else if (ind == e_exit)
	// 	ft_exit(cmd_lst);
}

char	*check_access(char *cmd)
{
	char	**temp;
	char	*path;

	temp = ft_split(getenv("PATH"), ':');
	cmd = ft_strjoin("/", cmd);
	while (*temp)
	{
		path = ft_strjoin(*temp, cmd);
		if (!access(ft_strjoin(*temp, cmd), F_OK | R_OK | X_OK))
		{
			ft_free(temp);
			return (path);
		}
		temp++;
	}
	ft_free(temp);
	free(path);
	return (NULL);
}

void	simple_cmd(t_cmd *cmd_lst)
{
	int		ind, pid;
	char	*path;

	if ((ind = is_builtin(*cmd_lst->cmd)))
		excute_builtin(cmd_lst, ind);
	else
	{
		pid = fork();
		if (!pid)
		{
			if ((path = check_access(*cmd_lst->cmd)))
				execve(path, cmd_lst->cmd, global.envp);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	ft_dup(t_cmd *cmd_lst)
{
	if (cmd_lst->in != 0)
	{
		dup2(cmd_lst->in, 0);
		close(cmd_lst->in);
	}
	if (cmd_lst->out != 1)
	{
		dup2(cmd_lst->out, 1);
		close(cmd_lst->out);
	}
}

int	child(t_cmd *cmd_lst)
{
	int		pid;
	int		ind;
	char	*path;

	pid = fork();
	if (!pid)
	{
		ft_dup(cmd_lst);
		if ((ind = is_builtin(*cmd_lst->cmd)))
		{
			excute_builtin(cmd_lst, ind);
			exit(0);
		}
		else if ((path = check_access(*cmd_lst->cmd)))
		{
			execve(path, cmd_lst->cmd, global.envp);
			exit(1);
		}
	}
	return (pid);
}

void	excute(t_cmd *cmd_lst)
{
	int		fds[2], pid;
	int		cmd_num;

	cmd_num = cmd_count(cmd_lst);
	if (cmd_num == 1)
	{
		simple_cmd(cmd_lst);
		return ;
	}
	while (cmd_lst)
	{
		if (cmd_lst->next)
		{
			pipe(fds);
			cmd_lst->out = fds[1];
			cmd_lst->next->in = fds[0];
		}
		pid = child(cmd_lst);
		close(fds[1]);
		cmd_lst = cmd_lst->next;
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid, NULL, 0);
}

void	envlist_addback(t_envlist **head, t_envlist *new)
{
	t_envlist	*temp;

	if (*head)
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*head = new;
}

t_envlist	*envlist_new(char *str)
{
	char		**temp;
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (ft_strchr(str, '='))
	{
		temp = ft_split(str, '=');
		new->key = *temp++;
		new->value = *temp;
		new->sep = '=';
	}
	else
	{
		new->key = str;
		new->value = 0;
		new->sep = 0;
	}
	new->next = NULL;
	return (new);
}

void	envlist_init(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
		envlist_addback(&global.envlist, envlist_new(envp[i++]));
	global.envp = envp;
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*line = NULL;
// 	t_cmd	cmd_lst;

// 	(void)ac;
// 	(void)av;
// 	envlist_init(envp);
// 	while ((line = readline("minishell>>")))
// 	{
// 		cmd_lst.cmd = ft_split(line, ' ');
// 		excute(&cmd_lst);
// 	}
// }
