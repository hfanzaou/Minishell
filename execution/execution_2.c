/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 03:33:37 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 03:53:41 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_handler(int signum)
{
	if (signum == SIGINT)
		write(2, "\n", 1);
	if (signum == SIGQUIT)
		write(2, "Quit: 3\n", 8);
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

int	str_search(char **haystack, char *needle)
{
	int	i;

	i = 0;
	if (!needle || !(*needle))
		return (0);
	while (haystack[i])
	{
		if (!ft_strcmp(haystack[i], needle))
			return (i + 1);
		i++;
	}
	return (0);
}

void	envlist_init(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		envlist_addback(&g_global.envlist, envlist_new(env[i++]));
}
