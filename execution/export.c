/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:24:39 by ajana             #+#    #+#             */
/*   Updated: 2022/12/22 23:33:18 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envlist_to_tab(void)
{
	t_envlist	*temp;
	char		*join;
	int			i;

	i = 0;
	temp = global.envlist;
	global.envp = realloc(global.envp, sizeof(char *) * (global.env_size + 1));
	while (temp)
	{
		if (temp->value)
		{
			join = ft_strjoin(temp->key, temp->sep);
			(global.envp)[i] = ft_strjoin(join, temp->value);
			free(join);
		}
		temp = temp->next;
		i++;
	}
	(global.envp)[i] = NULL;
}

void	print_envlist(void)
{
	t_envlist	*temp;

	temp = global.envlist;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->key, 1);
		if (temp->value)
		{
			ft_putchar_fd(temp->sep[ft_strlen(temp->sep) - 1], 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\"', 1);
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
		if (!ft_strcmp(temp->key, needle->key))
		{
			if (*needle->sep == '+' && (needle->value))
				temp->value = ft_strjoin(temp->value, needle->value);
			else if (needle->value)
				temp->value = needle->value;
			temp->sep = "=";
			envlist_to_tab();
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	add_to_env(char **args)
{
	t_envlist	*temp;

	while (*args)
	{
		temp = envlist_new(*args);
		if (!(temp))
		{
			ft_putstr_fd("MINISHELL: export: ", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		if (search_nd_replace(temp))
		{
			temp->sep = "=";
			if (temp->value)
				(global.env_size)++;
			envlist_addback(&(global.envlist), temp);
			envlist_to_tab();
		}
		else
			free(temp);
		args++;
	}
	return (0);
}

int	export(char **cmd)
{
	printf("%d\n", global.env_size);
	if (cmd[1])
		return (add_to_env(cmd + 1));
	else
		print_envlist();
	return (0);
}
