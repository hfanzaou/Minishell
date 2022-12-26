/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:51:34 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/26 06:51:57 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handler(int i)
{
	if (i == SIGINT)
	{
		//rl_on_new_line();
		printf("\n"); // Move to a new line
		 // Regenerate the prompt on a newline
		//readline("MINISHELL>");// Clear the previous text
    	rl_redisplay();
		
	}
}

t_cmd *init_cmd(char **cargs, int in, int out, int flag)
{
	t_cmd *cmd;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
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
	(global.envp) = (char **)malloc(sizeof(char *) * (global.env_size + 1));
	while (env[l])
	{
		i = 0;
		(global.envp)[l] = (char *)malloc(sizeof(char) * ft_strlen(env[l]) + 1);
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
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_lexer *lexer;
	token_t *token;
	t_cmd *cmd;

	// signal(SIGINT, handler);
	put_env(env);
	envlist_init();
	while ((line = readline("MINISHELL>")))
	{
		if (line[0])
		{ 
			add_history(line);
			//cmd = init_cmd();
			lexer = ft_lexer(line);
			token = tokenizer(lexer);
			cmd = ft_parse(token, cmd);
			if (!cmd)
				continue;
			excute(cmd);
			//ft_free(cmd->cmd);
			// close(cmd->out);
			free(cmd);
			free(lexer);
			free(token);
			cmd = NULL;
			lexer = NULL;
			token = NULL;
		}
	}
}