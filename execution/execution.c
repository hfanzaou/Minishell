/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:49:46 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 08:12:20 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	child(t_cmd *cmd_lst)
{
	int		ind;
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_dup(cmd_lst);
	ind = is_builtin(*(cmd_lst->cmd));
	if (ind)
		exit(execute_builtin(cmd_lst, ind, 0));
	path = check_access(*(cmd_lst->cmd));
	if (path)
	{
		execve(path, cmd_lst->cmd, envlist_to_tab());
		perror("execve");
		exit(1);
	}
	else
	{
		ft_error("minishell: ", *(cmd_lst->cmd), ": command not found\n");
		exit(127);
	}
}

int	ft_fork(t_cmd *cmd_lst)
{
	int	pid;

	if (!(cmd_lst->cmd))
	{
		g_global.exit_status = 0;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		child(cmd_lst);
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
	return (pid);
}

int	simple_cmd(t_cmd *cmd_lst)
{
	int		ind;
	int		tmpin;
	int		tmpout;

	if (!(cmd_lst->cmd))
	{
		g_global.exit_status = 0;
		return (0);
	}
	ind = is_builtin(*(cmd_lst->cmd));
	if (ind)
	{
		tmpin = dup(0);
		tmpout = dup(1);
		ft_dup(cmd_lst);
		g_global.exit_status = execute_builtin(cmd_lst, ind, 1);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
	}
	else
		return (ft_fork(cmd_lst));
	return (0);
}

void	open_pipe(t_cmd *cmd_lst)
{
	int	fds[2];

	if (cmd_lst->next)
	{
		if (pipe(fds))
			return (perror("minishell: pipe"));
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

	pid = 0;
	if (!cmd_lst)
		return ;
	if (!(cmd_lst->next))
	{
		pid = simple_cmd(cmd_lst);
		cmd_lst = NULL;
	}
	while (cmd_lst)
	{
		if (cmd_lst->next)
			open_pipe(cmd_lst);
		pid = ft_fork(cmd_lst);
		if (cmd_lst->out != 1)
			close(cmd_lst->out);
		if (cmd_lst->in != 0)
			close(cmd_lst->in);
		cmd_lst = cmd_lst->next;
	}
	if (pid)
		waitpid(pid, &(g_global.exit_status), 0);
	while (wait(NULL) != -1)
		;
}
