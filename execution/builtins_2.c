/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 03:21:51 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 09:03:09 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_option(char *arg)
{
	int	i;

	if (*arg != '-')
		return (1);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (cmd[i])
	{
		if (check_option(cmd[i]))
		{
			print_args(&(cmd[i]));
			break ;
		}
		else
			option = 1;
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '+' || arg[i] == '-' ) && (!i))
			;
		else if (!ft_isdigit(arg[i]))
		{
			ft_error("minishell: exit: ", arg, ": numeric argument required\n");
			exit(255);
		}
		i++;
	}
}

int	ft_exit(char **cmd, int print)
{
	int	i;
	int	ex_status;

	i = 0;
	if (print)
		ft_putstr_fd("exit\n", 1);
	if (!(cmd[1]))
		exit (WEXITSTATUS(g_global.exit_status));
	check_arg(cmd[1]);
	if ((cmd[2]))
	{
		ft_error("minishell: exit: ", NULL, "too many arguments\n");
		return (256);
	}
	ex_status = ft_atoi(*(cmd + 1));
	if (ex_status > 255 || ex_status < 0)
		exit (ex_status % 256);
	exit(ex_status);
}
