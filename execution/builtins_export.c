/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:24:39 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 10:15:46 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_envlist(void)
{
	t_envlist	*temp;

	temp = g_global.envlist;
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

t_envlist	*envlist_search(char *key)
{
	t_envlist	*temp;

	temp = g_global.envlist;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	replace_value(t_envlist *needle)
{
	t_envlist	*temp;
	char		*to_free;

	temp = envlist_search(needle->key);
	if (temp)
	{	
		to_free = temp->value;
		free(needle->key);
		if (*needle->sep == '+' && (needle->value))
		{
			temp->value = ft_strjoin(temp->value, needle->value);
			free(needle->value);
			free(to_free);
		}
		else if (needle->value)
		{
			temp->value = needle->value;
			free(to_free);
		}
		temp->sep = "=";
		return (0);
	}
	return (1);
}

int	add_to_env(char **args)
{
	t_envlist	*temp;
	int			ret;

	ret = 0;
	while (*args)
	{
		temp = envlist_new(*args);
		if (!(temp))
		{
			ret = ft_ret(*args);
			args++;
			continue ;
		}
		if (replace_value(temp))
		{
			temp->sep = "=";
			(g_global.env_size)++;
			envlist_addback(&(g_global.envlist), temp);
		}
		else
			free(temp);
		args++;
	}
	return (ret);
}

int	export(char **cmd)
{
	if (cmd[1])
		return (add_to_env(cmd + 1));
	else
		print_envlist();
	return (0);
}
