/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:29:49 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/20 17:10:36 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_endch(char const *s1, char const *set)
{
	size_t	i;
	size_t	l;

	l = ft_strlen(s1) - 1;
	while (l > 0)
	{
		i = 0;
		while (set[i])
		{
			if (s1[l] == set[i])
				break ;
			i++;
		}
		if (set[i] == '\0')
			return (l + 1);
		l--;
	}
	return (0);
}

static size_t	ft_startch(char const *s1, char const *set)
{
	size_t	i;
	size_t	l;

	i = 0;
	while (*s1)
	{
		l = 0;
		while (set[l])
		{
			if (*s1 == set[l])
			{
				i++;
				break ;
			}
			l++;
		}
		if (set[l] == '\0')
			return (i);
		s1++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*c;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	i = ft_startch(s1, set);
	j = ft_endch(s1, set);
	c = malloc(sizeof(char) * (j - i + 1));
	if (c == NULL)
		return (0);
	j = 0;
	while (i + j < ft_endch(s1, set) && *s1)
	{
		c[j] = *(s1 + i + j);
		j++;
	}
	c[j] = '\0';
	return (c);
}
