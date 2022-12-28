/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:51:34 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:09:34 by ajana            ###   ########.fr       */
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
		rl_on_new_line();
		write(1, "\n", 1);
    	rl_redisplay();
	}
}

t_cmd *init_cmd(char **cargs, int in, int out, int flag)
{
	t_cmd *cmd;
	cmd = (t_cmd *)s_malloc(sizeof(t_cmd));
	cmd->cmd = cargs;
	cmd->fd = 0;
	cmd->in = in;
	cmd->out = out;
	cmd->err = flag;
	cmd->next = NULL;
	return (cmd);
}

int envlen(char **env)
{
	int i;
	i = 0;
	while (env[i])
		i++;
	return (i);	
}

void	ft_free2(void **str)
{
	int i;

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

void	enter(t_lexer *lex)
{
	if (lex->f == 1)
	{
		g_global.exit_status = 0;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_lexer *lexer;
	t_token *token;
	t_cmd *cmd;
	(void)env;
	cmd = NULL;
	signal(SIGINT, handler);
	//put_env(env);
	envlist_init(env);
	while (1)
	{
		g_global.index = 0;
		line = readline("minishell>>");
		if (!line)
			exit_bash(line);
		else if (!(*line))
			continue ;
		add_history(line);
		lexer = ft_lexer(line);
		token = tokenizer(lexer);
		cmd = ft_parse(token, cmd);
		if (!cmd)
		{
			free(line);
			g_global.exit_status = 256;
			continue ;
		}
		excute(cmd);
		free(line);
		ft_free2(g_global.to_free);
		//system("leaks minishell");
		cmd = NULL;
		lexer = NULL;
		token = NULL;
	}
}
	
