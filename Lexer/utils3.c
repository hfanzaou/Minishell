/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:00:25 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 14:36:12 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	*s_malloc(int size)
{
	void	*tmp;

	tmp = malloc(size);
	g_global.to_free[g_global.index] = tmp;
	g_global.index++;
	return (tmp);
}

void	exit_path(char *cmd)
{
	ft_error("minishell: ", cmd, ": No such file or directory\n");
	exit(127);
}

void	handler(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_global.exit_status = 256;
	}
}

void	ft_free2(void **str)
{
	int	i;

	i = 0;
	while (i < g_global.index)
	{
		free(str[i]);
		i++;
	}
}

void	exit_bash(char *line, int f)
{
	if (f)
		printf("exit\n");
	exit(WEXITSTATUS(g_global.exit_status));
	ft_free2(g_global.to_free);
	free(line);
}
