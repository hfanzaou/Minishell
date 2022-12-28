/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:33:25 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 15:53:09 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "token.h"

void	printf_token(t_token *token)
{
	printf("In token\n");
	while (token)
	{
		printf("type  = %d\n", token->e_type);
		printf("value = %s\n", token->value);
		printf("flag = %d\n", token->err);
		token = token->next;
	}
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
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
