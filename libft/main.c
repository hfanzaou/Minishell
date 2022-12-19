/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:39:23 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 20:14:14 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	*f(void *i)
{
	*(int *)i = *(int *)i + 1;
	return i;
}

void	del(void *i)
{
	*(int *)i = 0;
	free(i);
}

int main()
{
	int tab[] = {0, 1, 2, 4};
	int i = 1;
	t_list *ptr = ft_lstnew(tab);
	while (i < 4)
	{
		ft_lstadd_back(&ptr, ft_lstnew(tab + i));
		i++;	
	}
	t_list *l = ft_lstmap(ptr, f, del);
	while (l != NULL)
	{
		printf("%d\n", *(int *)l->content);
		l = l->next;	
	}
	return 0;
}
