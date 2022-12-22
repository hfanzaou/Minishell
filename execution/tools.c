/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:43:06 by ajana             #+#    #+#             */
/*   Updated: 2022/12/22 23:35:03 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	while (*str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
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
