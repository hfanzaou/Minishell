/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:49:46 by ajana             #+#    #+#             */
/*   Updated: 2022/12/23 01:43:10 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*builtins;
	int		i;

	builtins = "echo cd pwd export unset env exit";
	if ((i = str_search(ft_split(builtins, ' '), cmd)))
		return (i);
	return (0);
}

int	excute_builtin(t_cmd *cmd_lst, int ind)
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
	// else if (ind == e_exit)
	// 	ft_exit(cmd_lst);
	return (127);
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
	int		ind;
	int		pid;
	int		tmpin;
	int		tmpout;
	char	*path;

	tmpin = dup(0);
	tmpout = dup(1);
	ft_dup(cmd_lst);
	if ((ind = is_builtin(*(cmd_lst->cmd))))
		global.exit_status = excute_builtin(cmd_lst, ind);
	else if ((path = check_access(*cmd_lst->cmd)))
	{
		pid = fork();
		if (!pid)
			execve(path, cmd_lst->cmd, global.envp);
		else
			waitpid(pid, &(global.exit_status), 0);
	}
	else
	{
		printf ("MINISHELL: %s: command not found\n", *cmd_lst->cmd);
		global.exit_status = 127;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
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
			global.exit_status = excute_builtin(cmd_lst, ind);
			exit(0);
		}
		else if ((path = check_access(*cmd_lst->cmd)))
		{
			if(execve(path, cmd_lst->cmd, global.envp))
				exit(1);
		}
		else
		{
			printf ("MINISHELL: %s: command not found\n", *cmd_lst->cmd);
			exit(127);
		}
	}
	return (pid);
}

void	excute(t_cmd *cmd_lst)
{
	int	fds[2];
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
		if (cmd_lst->next)
		{
			pipe(fds);
			if (cmd_lst->out == 1)
				cmd_lst->out = fds[1];
			if (cmd_lst->next->in == 0)
				cmd_lst->next->in = fds[0];
		}
		pid = child(cmd_lst);
		close(fds[1]);
		cmd_lst = cmd_lst->next;
	}
	close(fds[0]);
	while (waitpid(-1, &(global.exit_status), 0) != -1);
}
