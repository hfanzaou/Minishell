/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:19:44 by ajana             #+#    #+#             */
/*   Updated: 2022/12/13 13:30:30 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef enum	builtins
{
	e_echo = 1,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit
}	t_builtins;

typedef	struct envlist
{
	char			*key;
	char			*value;
	char			sep;
	struct	envlist	*next;
}	t_envlist;

typedef	struct global
{
	t_envlist	*envlist;
	char		**envp;
} t_global;

typedef struct	s_cmd
{
	char	**cmd;
	int		in;
	int		out;
	int		fd;
	struct	s_cmd *next;
}	t_cmd;

extern t_global	global;

void		echo(t_cmd *cmd_lst);
void		cd(t_cmd *cmd_lst);
void		pwd();
void		export(t_cmd *cmd_lst);
void		unset(t_cmd *cmd_lst);
void		env();
void		ft_exit(t_cmd *cmd_lst);
t_envlist	*envlist_new(char *str);
void		envlist_addback(t_envlist **head, t_envlist *new);

#endif
