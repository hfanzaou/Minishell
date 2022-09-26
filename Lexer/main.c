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

t_cmd *init_cmd()
{
	t_cmd *cmd;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmd = (char **)malloc(sizeof(char *));
	cmd->fd = -1;
	cmd->in = -1;
	cmd->out = -1;
	return (cmd);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_lexer *lexer;
	token_t *token;
	t_cmd *cmd;
	signal(SIGINT, handler);
	while ((line = readline("MINISHELL>")))
	{
		//printf("%s\n", line); 
		add_history(line);
		cmd = init_cmd();
		lexer = ft_lexer(line);
		token = tokenizer(lexer, env);
		cmd = ft_parse(token);	
	}
}

