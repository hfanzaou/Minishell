/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 06:38:07 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 14:26:25 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	herdoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		unlink("/tmp/herdoc_file");
		exit(1);
	}
}

char	*joinex(char *line)
{
	int i;
	char *c;
	char *val;

	c = ft_strdup2(" ");
	val = ft_strdup2("");
	i = 0;
	while (line[i])
	{	
		c[0] = line[i];
		c[1] = '\0';
		if (line[i] == '$')
		{
			val = ft_strjoin2(val, ft_expand(&line[i], global.envp, NULL, 0), strlen(val));
			i += ft_skip(&line[i + 1]);
		}
		else
			val = ft_strjoin2(val, c, ft_strlen(val));
		if (!line[i])
			break;
		i++;
	}
	return (val);
}

int	ft_herdoc(char *eof, int here)
{
	int i;
	char *line;
	char *str;
	int	fd;

	i = fork();
	fd = 0;
	fd = open("/tmp/herdoc_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (i == 0)
	{
		signal(SIGINT, herdoc_handler);
		while ((line = readline(">")))
		{
			str = line;
			if (!ft_strrchr(line, '$') && here == 0)
				str = joinex(line);
			if (!ft_strrchr(line, '$') && !ft_strcmp(joinex(line), eof))
				exit(0);
			else if (ft_strcmp(str, eof))
			{
				write(fd, str, strlen(str));
				write(fd, "\n", 1);
			}
			else if (!ft_strcmp(line, eof))
				exit(0);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&i);
	}
	return (fd);
}
