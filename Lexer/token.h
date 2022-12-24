/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:00:02 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/23 01:42:27 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdlib.h>
# include "lexer.h"

typedef struct token_s
{
	char *value;
	struct token_s *next;
	enum
	{
		STRING,
		SINGLE_Q,
		DOUBLE_Q,
		RED_IN,
		RED_OUT,
		RED_IN2,
		RED_OUT2,
		PIPE,
		DOLLAR,
		EXIT,
		//SPACE,
		END
	} type;
}	token_t;

t_cmd *init_cmd(char **cargs, int in, int out);
void printf_token(token_t *token);
token_t *tokenizer(t_lexer *lexer);
token_t *token_init(char *val, int type);
t_cmd *ft_parse(token_t *token, t_cmd *cmd);
char	*ft_realloc(char *str, int j);
# endif  
