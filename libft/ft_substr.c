/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:51:18 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 00:41:12 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	char	*c;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s) || !*s || !len)
	{
		c = ft_strdup("\0");
		return (c);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	i = 0;
	c = malloc(sizeof(char) * len + 1);
	if (!c)
		return (0);
	while (i < len)
	{
		c[i] = s[start + i];
		i++;
	}
	c[i] = '\0';
	return (c);
}
