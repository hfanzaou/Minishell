/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:00:25 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 15:53:12 by hfanzaou         ###   ########.fr       */
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

void	save_add(char *save)
{
	g_global.to_free[g_global.index] = save;
	g_global.index++;
}

void	handler(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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

void	exit_bash(char *line)
{
	printf("exit\n");
	exit(WEXITSTATUS(g_global.exit_status));
	free(line);
}
