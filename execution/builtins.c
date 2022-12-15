/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:26:17 by ajana             #+#    #+#             */
/*   Updated: 2022/12/13 17:25:19 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **cmd)
{
	t_envlist	*temp;

	if (cmd[1])
	{
		ft_putstr_fd("env: No arguments or options are allowed\n", 2);
		return ;
	}
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

void	echo(char **cmd)
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
}

void	pwd()
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_putstr_fd(wd, 1);
	ft_putstr_fd("\n", 1);
}

void	cd(char **cmd)
{
	int	ret;

	if (!(cmd[1]) || (*(cmd[1])) == '~')
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(cmd[1]);
	if (ret)
		perror("cd");
}

void	envlist_delete(char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;

	curr = global.envlist;
	while (curr && ft_strncmp(key, curr->key, ft_strlen(curr->key)))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	free(curr);
	curr = NULL;
}

void	unset(char **cmd)
{
	while (*(++cmd))
		envlist_delete(*cmd);
}