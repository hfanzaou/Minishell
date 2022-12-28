/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 06:38:07 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 06:38:10 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parse.h"

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
	int fd[2];

	pipe(fd);
	i = fork();
	if (i == 0)
	{
		while ((line = readline(">")))
		{
			str = line;
			if (!ft_strrchr(line, '$') && here == 0)
				str = joinex(line);
			if (!ft_strrchr(line, '$') && !ft_strcmp(joinex(line), eof))
				exit(0);
			else if (ft_strcmp(str, eof))
			{
				write(fd[1], str, strlen(str));
				write(fd[1], "\n", 1);
			}
			else if (!ft_strcmp(line, eof))
				exit(0);
		}
	}
	else
	{
		wait(&i);
		close(fd[1]);
	}
	return (fd[0]);	
}
