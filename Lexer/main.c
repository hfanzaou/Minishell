/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:51:34 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/09 15:51:35 by hfanzaou         ###   ########.fr       */
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

t_cmd *init_cmd(char **cargs, int in, int out)
{
	t_cmd *cmd;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmd = cargs;
	cmd->fd = 0;
	cmd->in = in;
	cmd->out = out;
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

char **put_env(char **env)
{
	char **myenv;
	int l;
	int i;
	l = envlen(env);
	myenv = (char **)malloc(sizeof(char *) * (l + 1));
	l = 0;
	while (env[l])
	{
		myenv[l] = (char *)malloc(sizeof(char) * ft_strlen(env[l]) + 1);
		i = 0;
		while (env[l][i])
		{
			myenv[l][i] = env[l][i];
			i++;
		}
		myenv[l][i] = '\0';
		l++;
	}
	myenv[l] = NULL;
	return (myenv);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	//char **myenv;
	t_lexer *lexer;
	token_t *token;
	t_cmd *cmd;
	signal(SIGINT, handler);
	//myenv = put_env(env);
	while ((line = readline("MINISHELL>")))
	{
		if (line[0])
		{ 
			add_history(line);
			//cmd = init_cmd();
			lexer = ft_lexer(line);
			token = tokenizer(lexer, env);
			cmd = ft_parse(token, cmd);
			close(cmd->out);
			free(cmd);
			free(lexer);
			free(token);
			cmd = NULL;
			lexer = NULL;
			token = NULL;
		}
	}
}

