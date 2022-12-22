/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:26:17 by ajana             #+#    #+#             */
/*   Updated: 2022/12/22 23:26:14 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		ft_putstr_fd("env: No arguments or options are allowed\n", 2);
		return (1);
	}
	while ((global.envp)[i])
	{
		ft_putstr_fd((global.envp)[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

int	echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
	return (0);
}

int	pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_putstr_fd(wd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int	cd(char **cmd)
{
	int	ret;

	if (!(cmd[1]) || (*(cmd[1])) == '~')
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(cmd[1]);
	if (ret)
	{
		ft_putstr_fd("MINISHELL: cd: ", 2);
		perror(cmd[1]);
		return (1);
	}
	return (0);
}

int	unset(char **cmd)
{
	while (*(++cmd))
		envlist_delete(*cmd);
	envlist_to_tab();
	return (0);
}
