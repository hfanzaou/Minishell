/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:51:34 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 03:01:31 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ret(char *line, int w)
{
	if (w == 2)
		g_global.exit_status = 256;
	free(line);
	ft_free2(g_global.to_free);
	return (w);
}

int	start(char *line, t_lexer *lexer)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	lexer = NULL;
	token = NULL;
	line = readline("minishell>>");
	if (!line)
		exit_bash(line, 1);
	else if (!(*line))
		return (ret(line, 1));
	add_history(line);
	lexer = ft_lexer(line);
	token = tokenizer(lexer);
	cmd = ft_parse(token, cmd);
	if (!cmd)
		return (ret(line, 2));
	excute(cmd);
	return (ret(line, 0));
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*lexer;

	(void)ac;
	(void)av;
	lexer = NULL;
	line = NULL;
	g_global.env_size = envlen(env);
	envlist_init(env);
	while (1)
	{
		g_global.index = 0;
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		if (start(line, lexer))
			continue ;
	}
}
