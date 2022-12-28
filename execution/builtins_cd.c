/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 03:15:53 by ajana             #+#    #+#             */
/*   Updated: 2022/12/28 03:19:04 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	update_pwd(char *oldpwd)
{
	t_envlist	*temp;

	temp = envlist_search("OLDPWD");
	if (temp)
	{
		temp->value = oldpwd;
		envlist_to_tab();
	}
	temp = envlist_search("PWD");
	if (temp)
	{
		temp->value = getcwd(NULL, 0);
		save_add(temp->value);
		envlist_to_tab();
	}
}

int	chdir_home()
{
	t_envlist	*temp;

	temp = envlist_search("HOME");
	if (!temp)
	{
		ft_error("minishell: cd: ", NULL, "HOME not set\n");
		return (1);
	}
	return (chdir(temp->value));
}

int	chdir_check(char *path)
{
	int		check;
	char	*dir;

	check = chdir(dir);
	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_error("cd: error retreiving current working directory: ", NULL, NULL);
		perror("getcwd: ");
		free(dir);
		return (1);
	}
	free(dir);
	return (check);
}

int	cd(char **cmd)
{
	char		*oldpwd;
	char		dir;
	int			ret;

	oldpwd = getcwd(NULL, 0);
	save_add(oldpwd);
	if (!(cmd[1]))
		ret = chdir_home();
	else
		ret = chdir_check(cmd[1]);
	if (ret == 0)
		update_pwd(oldpwd);
	else if (ret == -1)
	{
		ft_error("minishell: cd: ", cmd[1], ": ");
		perror(NULL);
		return (256);
	}
	return (0);
}
