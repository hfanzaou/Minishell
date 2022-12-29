/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:37:10 by ajana             #+#    #+#             */
/*   Updated: 2022/12/29 10:18:32 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_node(t_envlist *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	envlist_delete(char *key)
{
	t_envlist	*curr;
	t_envlist	*prev;

	curr = g_global.envlist;
	prev = curr;
	while (curr && ft_strcmp(key, curr->key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (prev == curr)
	{
		g_global.envlist = g_global.envlist->next;
		free_node(curr);
		return ;
	}
	prev->next = curr->next;
	(g_global.env_size)--;
	free_node(curr);
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
	if (!key)
		return (NULL);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && (key[i] != '_'))
		{
			if ((key[i] == '+') && (!key[i + 1]))
				return ("+=");
			return (NULL);
		}
		else if (ft_isdigit(key[i]) && i == 0)
			return (NULL);
		i++;
	}
	return ("=");
}

t_envlist	*envlist_new(char *str)
{
	char		**temp;
	t_envlist	*new;
	char		*search;

	temp = ft_split(str, '=');
	new = malloc(sizeof(t_envlist));
	new->sep = keycheck(*temp);
	if (!(new->sep))
	{
		free(new);
		free(temp);
		return (ft_free(temp, 0));
	}
	else if (*new->sep == '+')
		(*temp)[ft_strlen(*temp) - 1] = '\0';
	new->key = *temp;
	ft_free(temp, 1);
	free(temp);
	search = ft_strchr(str, '=');
	if (search)
		new->value = ft_strdup(search + 1);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
