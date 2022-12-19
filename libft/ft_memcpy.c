/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:51:50 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 20:42:22 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*l;

	if (!dst && !src)
		return (0);
	c = (unsigned char *)dst;
	l = (unsigned char *)src;
	i = 0;
	while (i < n && c != l)
	{
		c[i] = l[i];
		i++;
	}
	return (dst);
}
