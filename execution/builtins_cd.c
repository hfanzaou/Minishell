/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 03:15:53 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 04:09:33 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	update_pwd(char *oldpwd)
{
	t_envlist	*temp;
	char		*to_free;

	temp = envlist_search("OLDPWD");
	to_free = temp->value;
	if (temp)
	{
		temp->value = oldpwd;
		free(to_free);
	}
	temp = envlist_search("PWD");
	to_free = temp->value;
	if (temp)
	{
		temp->value = getcwd(NULL, 0);
		free(to_free);
	}
}

int	chdir_home(void)
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

	check = chdir(path);
	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_error("cd: error retreiving current working directory: ",
			NULL, NULL);
		perror("getcwd: ");
		return (1);
	}
	free(dir);
	return (check);
}

int	cd(char **cmd)
{
	char		*oldpwd;
	int			ret;

	oldpwd = getcwd(NULL, 0);
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
