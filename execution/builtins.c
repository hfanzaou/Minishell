/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:26:17 by ajana             #+#    #+#             */
/*   Updated: 2022/12/24 18:08:58 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *cmd, char *arg, char *err)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg ,2);
	if (arg)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	return (1);
}

int	env(char **cmd)
{
	int	i;
	t_envlist	*temp;

	temp = global.envlist;
	i = 0;
	if (cmd[1])
	{
		ft_putstr_fd("env: No arguments or options are allowed\n", 2);
		return (1);
	}
	while ((temp))
	{
		if ((temp)->value)
		{	
			ft_putstr_fd((temp)->key, 1);
			ft_putstr_fd((temp)->sep, 1);
			ft_putstr_fd((temp)->value, 1);
		}		
		ft_putchar_fd('\n', 1);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	check_option(char *arg)
{
	int	i;

	if (*arg != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (cmd[i])
	{
		if (!check_option(cmd[i]))
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
		else
			option = 1;
		i++;
	}
	if (!option)
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

int	ft_exit(char **cmd)
{
	int	i;
	int	ex_status;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (!(cmd[i + 1]))
		exit (global.exit_status);
	cmd++;
	while ((*cmd)[i])
	{
		if (((*cmd)[i] == '+' || (*cmd)[i] == '-' ) && (!i));
		else if (!ft_isdigit((*cmd)[i]))
		{
			ft_error("MINISHELL: exit: ", *cmd,  "numeric argument required\n");
			exit (255);
		}
		i++;
	}
	if (*(cmd + 1))
		return (ft_error("MINISHELL: exit: ", NULL, "too many arguments\n"));
	ex_status = ft_atoi(*cmd);
	if (ex_status > 255 || ex_status < 0)
		exit (ex_status % 256);
	exit(ex_status);
}
