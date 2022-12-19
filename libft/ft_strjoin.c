/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:08:53 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/20 16:32:50 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*c;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	c = malloc(sizeof(char) * i + 1);
	if (c == NULL)
		return (0);
	j = 0;
	while (*s1)
	{
		c[j] = *s1++;
		j++;
	}
	while (*s2)
	{
		c[j] = *s2++;
		j++;
	}
	c[j] = '\0';
	return (c);
}
