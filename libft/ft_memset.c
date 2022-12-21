/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:58:39 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 22:23:27 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
/*
int main(int ac, char **av)
{
	int tab[6];
	(void)ac;
	ft_memset(tab, 10, 6 * sizeof(int));
	printf("%lu\n", sizeof(tab));
    for (int i = 0; i < 6; i++)
		printf("%d\n", tab[i]);
	ft_memset(av[1], '.', 2 * sizeof(char));
	memset(av[2], '.', 2 * sizeof(char));
	printf("%s\n", av[1]);
	printf("%s\n", av[2]);
}*/
