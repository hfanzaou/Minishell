/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:17:00 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 20:38:47 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1 && i < n)
	{
		j = 0;
		while (*(s1 + j) == *(s2 + j) && i + j < n)
		{	
			j++;
			if (!s2[j])
				return ((char *)s1);
		}
		s1++;
		i++;
	}	
	return (0);
}
