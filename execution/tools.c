/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:43:06 by ajana             #+#    #+#             */
/*   Updated: 2022/12/28 04:01:55 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	envlist_to_tab(void)
{
	t_envlist	*temp;
	char		*join;
	int			i;

	i = 0;
	temp = global.envlist;
	global.envp = s_malloc((global.env_size + 1) * sizeof(char *));
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

void	ft_error(char *cmd, char *arg, char *err)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg ,2);
	ft_putstr_fd(err, 2);
}

void	ft_free(char **str, int ind)
{
	while (str[ind])
	{
		free(str[ind]);
		*str = NULL;
		ind++;
	}
	str = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (1);
	return (0);
}

void	ft_dup(t_cmd *cmd_lst)
{
	if (cmd_lst->next)
		close(cmd_lst->next->in);
	if (cmd_lst->in != 0)
	{
		dup2(cmd_lst->in, 0);
		close(cmd_lst->in);
	}
	if (cmd_lst->out != 1)
	{
		dup2(cmd_lst->out, 1);
		close(cmd_lst->out);
	}
}

int	ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_search(char **haystack, char *needle)
{
	int	i;

	i = 0;
	if (!needle || !(*needle))
		return (0);
	while (haystack[i])
	{
		if (!ft_strcmp(haystack[i], needle))
			return (i + 1);
		i++;
	}
	return (0);
}
