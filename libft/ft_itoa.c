/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:22:07 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/17 14:10:12 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count(int n)
{
	unsigned int	i;
	int				j;

	i = n;
	if (n < 0)
		i = -n;
	j = 0;
	while (i != 0)
	{
		i /= 10;
		j++;
	}
	return (j);
}

static void	put_digit(char *c, unsigned int i, int j)
{
	while (i != 0)
	{
		j--;
		c[j] = (i % 10 + 48);
		i = i / 10;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	int				j;
	char			*c;

	j = ft_count(n);
	i = n;
	if (n <= 0)
	{
		i = -n;
		j += 1;
	}	
	c = malloc(sizeof(char) * j + 1);
	if (c == NULL)
		return (0);
	if (n < 0)
		*c = '-';
	if (!n)
		*c = '0';
	c[j] = '\0';
	put_digit(c, i, j);
	return (c);
}
