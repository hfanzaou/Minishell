/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:47 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 00:39:22 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*l;

	l = (unsigned char *)s;
	i = 0;
	if (!n)
		return (0);
	while (i < n)
	{
		if (l[i] == (unsigned char)c)
			return (&l[i]);
		i++;
	}
	return (0);
}
