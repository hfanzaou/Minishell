/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:33:25 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:33:28 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "token.h"

void printf_token(token_t *token)
{
	printf("In token\n");
	while (token)
	{
		printf("type  = %d\n", token->type);
		printf("value = %s\n", token->value);
		printf("flag = %d\n", token->err);
		token = token->next;
	}
}

token_t	*ft_lstlast(token_t *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	ft_lstadd_back(token_t **lst, token_t *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

t_cmd	*ft_lstlastc(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	ft_lstadd_backc(t_cmd **lst, t_cmd *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlastc(*lst)->next = new;
}
