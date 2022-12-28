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
# include "token.h"

void	ft_lstadd_backc(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlastc(t_cmd *lst);
char	**fillcargs(char **cargs, char *val);
void	ft_putstr_fd(char *s, int fd);
void	printcmd(t_cmd *cmd);
int		ft_herdoc(char *eof, int here);
int 	access_tokens(token_t *token);
int		ft_access_cond(token_t **token, char ***cargs);
int		if_access(token_t **token, char ***cargs);
int		what_fd(token_t *token);
int		what_type(token_t *token);
int 	if_ambiguous(token_t *token);
char	**to_cargs(char  **cargs, char *val);

# endif
