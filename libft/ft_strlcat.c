/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:30:28 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 20:41:14 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	size_t	i;

	ld = ft_strlen(dst);
	ls = ft_strlen((char *)src);
	i = 0;
	if (size && ld < size - 1)
	{	
		dst += ld;
		while (*src && ld + i < size - 1)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
	}	
	if (ld >= size)
		ld = size;
	return (ls + ld);
}
