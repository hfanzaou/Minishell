/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:19:44 by ajana             #+#    #+#             */
/*   Updated: 2022/12/20 22:50:22 by ajana            ###   ########.fr       */
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
	char			*sep;
	struct	envlist	*next;
}	t_envlist;

typedef	struct global
{
	t_envlist	*envlist;
	char		**envp;
	int			env_size;
} t_global;

typedef struct	s_cmd
{
	char	**cmd;
	int		in;
	int		out;
	int		fd;
	struct	s_cmd *next;
}	t_cmd;

t_global	global;

void		echo(char **cmd);
void		cd(char **cmd);
void		pwd();
void		export(char **cmd);
void		unset(char **cmd);
void		env(char **cmd);
t_envlist	*envlist_new(char *str);
void		envlist_addback(t_envlist **head, t_envlist *new);
int			ft_strcmp(char *s1, char *s2);
void		ft_free(char **str);
void		envlist_to_tab();

#endif
