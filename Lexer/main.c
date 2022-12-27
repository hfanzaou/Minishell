/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:51:34 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/27 19:00:03 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	*s_malloc(int size)
{
	void	*tmp;
	tmp = malloc(size);
	global.to_free[global.index] = tmp;
	global.index++;
	return (tmp);
}

void	save_add(char *save)
{
	global.to_free[global.index] = save;
	global.index++;
}

void	handler(int i)
{
	if (i == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		// rl_replace_line("", 0);
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

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);	
}

void	put_env(char **env)
{
	int l;
	int i;

	l = 0;
	global.env_size = envlen(env);
	(global.envp) = (char **)s_malloc(sizeof(char *) * (global.env_size + 1));
	while (env[l])
	{
		i = 0;
		(global.envp)[l] = (char *)s_malloc(sizeof(char) * ft_strlen(env[l]) + 1);
		while (env[l][i])
		{
			(global.envp)[l][i] = env[l][i];
			i++;
		}
		(global.envp)[l][i] = '\0';
		l++;
	}
	(global.envp)[l] = NULL;
	return ;
}

void	ft_free2(token_t *token)
{
	token_t *head;
	head = token;
	while (head)
	{
		free(head->value);
		head = head->next;
	}
	free(token);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_lexer *lexer;
	token_t *token;
	t_cmd *cmd;
	(void)env;
	global.index = 0;
	signal(SIGINT, handler);
	put_env(env);
	envlist_init();
	while ((line = readline("minishell>>")))
	{
		if (line[0] != '\0')
		{ 
			add_history(line);
			//cmd = init_cmd();
			lexer = ft_lexer(line);
			token = tokenizer(lexer);
			// free(lexer->src);
			// free(lexer);
			cmd = ft_parse(token, cmd);
			// ft_free2(&token);
			if (!cmd)
				continue;
			excute(cmd);
			// ft_free(cmd->cmd);
			// close(cmd->out);
			// free(cmd);
			// ft_free2(token);
			// ft_free(global.to_free);
			free(line);
			free(lexer);
			//free(token);
			//system("leaks minishell");
			cmd = NULL;
			lexer = NULL;
			token = NULL;
		}
	}
}