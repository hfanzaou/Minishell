/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:26:17 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 00:12:30 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	char	**builtins;
	char	*temp;
	int		ind;

	temp = "echo cd pwd export unset env exit";
	builtins = ft_split(temp, ' ');
	ind = str_search(builtins, cmd);
	ft_free(builtins, 0);
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

int	env(char **cmd)
{
	int			i;
	t_envlist	*temp;

	temp = g_global.envlist;
	i = 0;
	if (cmd[1])
	{
		ft_putstr_fd("env: No arguments or options are allowed\n", 2);
		return (256);
	}
	while ((temp))
	{
		if ((temp)->value)
		{	
			ft_putstr_fd((temp)->key, 1);
			ft_putstr_fd((temp)->sep, 1);
			ft_putstr_fd((temp)->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

int	pwd(void)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd)
	{
		ft_putstr_fd(wd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		free (wd);
		perror("minishell: pwd: error retreiving current working directory: ");
		return (256);
	}
	free(wd);
	return (0);
}

int	unset(char **cmd)
{
	char	*sep;
	int		ret;
	int		i;

	ret = 0;
	i = 1;
	while (cmd[i])
	{
		sep = keycheck(cmd[i]);
		if (!sep)
		{
			ft_error("minishell: unset: ", cmd[i], "not a valid idetifier\n");
			ret = 256;
		}
		// free (sep);
		envlist_delete(cmd[i]);
		i++;
	}
	return (ret);
}
