/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:20:33 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/16 08:12:58 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*c;
	char	*l;

	c = (char *)dst;
	l = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (l < c)
	{
		while (n--)
			c[n] = l[n];
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, n));
}
