/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:31:28 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 19:42:34 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*h;

	h = s_malloc(sizeof(t_list));
	if (h == NULL)
		return (0);
	h->content = content;
	h->next = NULL;
	return (h);
}
