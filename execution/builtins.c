/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:26:17 by ajana             #+#    #+#             */
/*   Updated: 2022/12/13 13:34:00 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envlist()
{
	t_envlist	*temp;

	temp = global.envlist;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->key, 1);
		if (temp->sep)
		{
			ft_putchar_fd(temp->sep, 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}

int	search_nd_replace(t_envlist *needle)
{
	t_envlist	*temp;

	temp = global.envlist;
	while (temp)
	{
		if (!ft_strncmp(needle->key, temp->key, ft_strlen(needle->key)))
		{
			if (needle->sep)
			{
				temp->value = needle->value;
				temp->sep = '=';
			}
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	add_to_env(char **args)
{
	t_envlist	*temp;

	while (*args)
	{
		temp = envlist_new(*args);
		if (search_nd_replace(temp))
			envlist_addback(&(global.envlist), temp);
		else
			free(temp);
		args++;
	}
}

void	export(t_cmd *cmd_lst)
{
	if ((cmd_lst->cmd)[1])
		add_to_env((cmd_lst->cmd) + 1);
	else
		print_envlist();
}

void	env()
{
	t_envlist	*temp;

	temp = global.envlist;
	while (temp)
	{
		if (temp->sep)
		{
			ft_putstr_fd(temp->key, 1);
			ft_putchar_fd(temp->sep, 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

void	echo(t_cmd *cmd_lst)
{
	(cmd_lst->cmd)++;
	while (*(cmd_lst->cmd))
	{
		ft_putstr_fd(*(cmd_lst->cmd), 1);
		ft_putchar_fd(' ', 1);
		(cmd_lst->cmd)++;
	}
	ft_putchar_fd('\n', 1);
}

void	pwd()
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_putstr_fd(wd, 1);
	ft_putstr_fd("\n", 1);
}

void	cd(t_cmd *cmd_lst)
{
	int	ret;

	if (!(cmd_lst->cmd[1]) || (*cmd_lst->cmd[1]) == '~')
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(cmd_lst->cmd[1]);
	if (ret)
		perror("cd");
}

void	envlist_delete(char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;

	curr = global.envlist;
	while (curr && ft_strncmp(key, curr->key, ft_strlen(key)))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	free(curr);
}

void	unset(t_cmd *cmd_lst)
{
	while (*(++cmd_lst->cmd))
		envlist_delete(*(cmd_lst->cmd));
}