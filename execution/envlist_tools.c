/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:37:10 by ajana             #+#    #+#             */
/*   Updated: 2022/12/22 23:34:00 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envlist_delete(char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;

	curr = global.envlist;
	while (curr && ft_strcmp(key, curr->key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	(global.env_size)--;
	free(curr);
	curr = NULL;
}

void	envlist_addback(t_envlist **head, t_envlist *new)
{
	t_envlist	*temp;

	if (*head)
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*head = new;
}

char	*keycheck(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && (key[i] != '_'))
		{
			if ((key[i] == '+') && (!key[i + 1]))
				return (ft_strdup("+="));
			return (NULL);
		}
		else if (ft_isdigit(key[i]) && i == 0)
			return (NULL);
		i++;
	}
	return (ft_strdup("="));
}

t_envlist	*envlist_new(char *str)
{
	char		**temp;
	t_envlist	*new;

	temp = ft_split(str, '=');
	new = malloc(sizeof(t_envlist));
	new->sep = keycheck(*temp);
	if (!(new->sep))
	{
		free(new);
		free(temp);
		return (NULL);
	}
	else if (*new->sep == '+')
		(*temp)[ft_strlen(*temp) - 1] = '\0';
	new->key = *temp;
	*temp = ft_strchr(str, '=');
	if (*temp)
		new->value = *(temp) + 1;
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	envlist_init(void)
{
	int	i;

	i = 0;
	while ((global.envp)[i])
		envlist_addback(&global.envlist, envlist_new((global.envp)[i++]));
}
