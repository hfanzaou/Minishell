/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:49:46 by ajana             #+#    #+#             */
/*   Updated: 2022/12/26 06:05:30 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_count(t_cmd *cmd_lst)
{
	t_cmd *temp;
	int		i = 0;

	temp = cmd_lst;
	while (temp) 
	{
		while (temp->cmd[i])
		{
			ft_putstr_fd(temp->cmd[i], 1);
			i++;
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

int	is_builtin(char *cmd)
{
	char	**builtins;
	char	*temp;
	int		ind;

	temp = "echo cd pwd export unset env exit";
	builtins = ft_split(temp, ' ');
	ind = str_search(builtins, cmd);
	free(builtins);
	return (ind);
}

int	execute_builtin(t_cmd *cmd_lst, int ind)
{
	if (ind == e_echo)
		return (echo(cmd_lst->cmd));
	else if (ind == e_cd)
		return (cd(cmd_lst->cmd));
	else if (ind == e_pwd)
		return (pwd());
	else if (ind == e_export)
		return (export(cmd_lst->cmd));
	else if (ind == e_unset)
		return (unset(cmd_lst->cmd));
	else if (ind == e_env)
		return (env(cmd_lst->cmd));
	else if (ind == e_exit)
		return (ft_exit(cmd_lst->cmd));
	return (1);
}

char	*relative_path(char *cmd)
{
	t_envlist	*node;
	char		**temp;
	char		*path;

	node = envlist_search("PATH");
	if (!node)
		return (NULL);
	temp = ft_split(node->value, ':');
	cmd = ft_strjoin("/", cmd);
	while (*temp)
	{
		path = ft_strjoin(*temp, cmd);
		if (!access(path, F_OK | R_OK | X_OK))
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

char	*check_access(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (cmd);
		ft_error("MINISHELL: ", cmd, "No such file or directory\n");
		exit (127);
	}
	return (relative_path(cmd));
}

int	child(t_cmd *cmd_lst)
{
	char	*path;
	int		pid;
	int		ind;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_lst->next)
			close(cmd_lst->next->in);
		ft_dup(cmd_lst);
		ind = is_builtin(*(cmd_lst->cmd));
		if (ind)
			exit(execute_builtin(cmd_lst, ind));
		path = check_access(*(cmd_lst->cmd));
		if (path)
		{
			execve(path, cmd_lst->cmd, global.envp);
			perror("execve");
			exit(1);
		}
		else
		{
			ft_error("minishell: ", *(cmd_lst->cmd), "command not found\n");
			exit(127);
		}
	}
	return (pid);
}

void	simple_cmd(t_cmd *cmd_lst)
{
	int		ind;
	int		pid;
	int		tmpin;
	int		tmpout;

	if (!(cmd_lst->cmd) || cmd_lst->err)
		return ;
	ind = is_builtin(*(cmd_lst->cmd));
	if (ind)
	{
		tmpin = dup(0);
		tmpout = dup(1);
		ft_dup(cmd_lst);
		global.exit_status = execute_builtin(cmd_lst, ind);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
	}
	else
	{
		pid = child(cmd_lst);
		waitpid(pid, &(global.exit_status), 0);
	}
}

void	open_pipe(t_cmd *cmd_lst)
{
	int	fds[2];

	if (cmd_lst->next)
	{
		pipe(fds);
		if (cmd_lst->out == 1)
			cmd_lst->out = dup(fds[1]);
		if (cmd_lst->next->in == 0)
			cmd_lst->next->in = dup(fds[0]);
		close(fds[1]);
		close(fds[0]);
	}
}

void	excute(t_cmd *cmd_lst)
{
	int	pid;

	if (!cmd_lst)
		return ;
	if (!(cmd_lst->next))
	{
		simple_cmd(cmd_lst);
		return ;
	}
	while (cmd_lst)
	{
		if (!(cmd_lst->cmd) || cmd_lst->err)
		{
			cmd_lst = cmd_lst->next;
			continue ;
		}
		if (cmd_lst->next)
			open_pipe(cmd_lst);
		pid = child(cmd_lst);
		if (cmd_lst->out != 1)
			close(cmd_lst->out);
		if (cmd_lst->in != 0)
			close(cmd_lst->in);
		cmd_lst = cmd_lst->next;
	}
	while(wait(&(global.exit_status)) != -1);
}
