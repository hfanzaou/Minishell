/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:19:44 by ajana             #+#    #+#             */
/*   Updated: 2022/12/26 23:35:42 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef enum builtins
{
	e_echo = 1,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit
}	t_builtins;

typedef struct envlist
{
	char			*key;
	char			*value;
	char			*sep;
	struct envlist	*next;
}	t_envlist;

typedef struct global
{
	t_envlist	*envlist;
	char		**envp;
	int			env_size;
	int			exit_status;
}	t_global;

typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	int				err;
	struct s_cmd	*next;
}	t_cmd;

t_global	global;

int			echo(char **cmd);
int			cd(char **cmd);
int			pwd(void);
int			export(char **cmd);
int			unset(char **cmd);
int			env(char **cmd);
int			ft_exit(char **cmd);
t_envlist	*envlist_new(char *str);
void		envlist_addback(t_envlist **head, t_envlist *new);
void		envlist_delete(char *key);
void		envlist_to_tab(void);
int			ft_strcmp(char *s1, char *s2);
void		ft_free(char **str, int ind);
void		ft_dup(t_cmd *cmd_lst);
int			str_search(char **haystack, char *needle);
void		ft_error(char *cmd, char *arg, char *err);
t_envlist	*envlist_search(char *key);
char		*keycheck(char *key);

#endif
