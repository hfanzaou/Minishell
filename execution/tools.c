/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:43:06 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 14:26:42 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**envlist_to_tab(void)
{
	t_envlist	*temp;
	char		*join;
	char		**env;
	int			i;

	i = 0;
	temp = g_global.envlist;
	env = malloc((g_global.env_size + 1) * sizeof(char *));
	if (!env)
		perror("malloc");
	while (temp)
	{
		if (temp->value)
		{
			join = ft_strjoin(temp->key, temp->sep);
			env[i] = ft_strjoin(join, temp->value);
			free(join);
		}
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_error(char *cmd, char *arg, char *err)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
}

void	*ft_free(char **str, int ind)
{
	while (str[ind])
	{
		free(str[ind]);
		str[ind] = NULL;
		ind++;
	}
	str = NULL;
	return (NULL);
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
