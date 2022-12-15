/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:24:39 by ajana             #+#    #+#             */
/*   Updated: 2022/12/13 17:25:40 by ajana            ###   ########.fr       */
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

void	export(char **cmd)
{
	if (cmd[1])
		add_to_env(cmd + 1);
	else
		print_envlist();
}