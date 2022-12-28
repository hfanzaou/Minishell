/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:49:46 by ajana             #+#    #+#             */
/*   Updated: 2022/12/28 05:37:54 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
			ft_free(temp, 0);
			return (path);
		}
		temp++;
	}
	ft_free(temp, 0);
	free(path);
	return (NULL);
}

char	*check_access(char *cmd)
{
	DIR	*dir;

	if (!(*cmd))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
		{
			dir = opendir(cmd);
			if (dir)
			{
				ft_error("minishell: ", cmd, ": is a directory\n");
				free(dir);
				exit(126);
			}
			return (cmd);
		}
		ft_error("minishell: ", cmd, ": No such file or directory\n");
		exit (127);
	}
	return (relative_path(cmd));
}

int	child(t_cmd *cmd_lst)
{
	char	*path;
	int		pid;
	int		ind;

	if (!(cmd_lst->cmd))
<<<<<<< HEAD
		return (0);
=======
	{
		global.exit_status = 0;
		return(0);
	}
>>>>>>> c180433a76ddacdb99c962525baa7c9152ea335e
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
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
			ft_error("minishell: ", *(cmd_lst->cmd), ": command not found\n");
			exit(127);
		}
	}
	signal(SIGINT, SIG_IGN);
	return (pid);
}

void	simple_cmd(t_cmd *cmd_lst)
{
	int		ind;
	int		pid;
	int		tmpin;
	int		tmpout;

	if (!(cmd_lst->cmd))
	{
		global.exit_status = 0;
		return ;
	}
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
			open_pipe(cmd_lst);
		pid = child(cmd_lst);
		if (cmd_lst->out != 1)
			close(cmd_lst->out);
		if (cmd_lst->in != 0)
			close(cmd_lst->in);
		cmd_lst = cmd_lst->next;
	}
	if (pid)
		waitpid(pid, &(global.exit_status), 0);
	while(wait(NULL) != -1);
}