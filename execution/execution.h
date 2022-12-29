/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:19:44 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 14:30:46 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"

enum e_builtins
{
	e_echo = 1,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit
};

typedef struct envlist
{
	char			*key;
	char			*value;
	char			*sep;
	struct envlist	*next;
}	t_envlist;

typedef struct g_global
{
	t_envlist	*envlist;
	int			env_size;
	int			exit_status;
	void		*to_free[1000000];
	int			index;
}				t_global;

typedef struct s_cmd
{
	char			**cmd;
	int				in;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

t_global	g_global;

/******builtins*****/
int			echo(char **cmd);
int			cd(char **cmd);
int			pwd(void);
int			export(char **cmd);
int			unset(char **cmd);
int			env(char **cmd);
int			ft_exit(char **cmd, int print);
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd_lst, int ind, int f);

/****envlist_tools****/
t_envlist	*envlist_new(char *str);
t_envlist	*envlist_search(char *key);
void		envlist_addback(t_envlist **head, t_envlist *new);
void		envlist_delete(char *key);
char		**envlist_to_tab(void);
void		free_node(t_envlist *node);
char		*retreive_key(char *str);

/****general_tools***/
int			ft_strcmp(char *s1, char *s2);
void		*ft_free(char **str, int ind);
void		ft_dup(t_cmd *cmd_lst);
int			str_search(char **haystack, char *needle);
void		ft_error(char *cmd, char *arg, char *err);
char		*keycheck(char *key);
void		*s_malloc(int size);
void		save_add(char *save);
char		*ft_strdup2(const char *s);
char		*ft_strjoin2(char const *s1, char const *s2, int n);
char		*relative_path(char *cmd);
char		*check_access(char *cmd);
void		child_handler(int signum);
void		exit_path(char *cmd);
int			ft_ret(char *args);

#endif
