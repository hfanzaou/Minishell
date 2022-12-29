/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:06:30 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 03:20:18 by hfanzaou         ###   ########.fr       */
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
int		access_tokens(t_token *token);
int		ft_access_cond(t_token **token, char ***cargs);
int		if_access(t_token **token, char ***cargs);
int		what_fd(t_token *token);
int		what_type(t_token *token);
int		if_ambiguous(t_token *token);
char	**to_cargs(char **cargs, char *val);

#endif