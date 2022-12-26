/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:30 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/26 17:06:32 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "lexer.h"
# include "token.h"

typedef struct s_cmd
{
	char **cmd;
	int in;
	int out;
	int fd;
	int err;
	struct s_cmd *next;
}	t_cmd;

t_cmd *ft_parse(token_t *token);
# endif
