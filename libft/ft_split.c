/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 05:42:26 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 20:19:51 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		if (*s != c && *s)
			i++;
		while (*s != c && *s)
			s++;
		if (!*s)
			break ;
		s++;
	}	
	return (i);
}

static char	*ft_strndup(const char *s, int n, char **b)
{
	char	*a;

	a = malloc(sizeof(char) * n + 1);
	if (a == NULL)
	{
		free(b);
		return (0);
	}
	ft_memcpy(a, s, n);
	a[n] = '\0';
	return (a);
}

static char	**ft_strmalldup(char **b, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		while (*s != c && *s)
		{
			i++;
			s++;
		}
		if ((*s == c && *s && *(s - 1) != c) || (!*s && *(s - 1) != c))
		{
			b[j] = ft_strndup(s - i, i, b);
			j++;
			i = 0;
		}
		if (!*s)
			break ;
		s++;
	}
	return (b);
}

char	**ft_split(char const *s, char c)
{
	char	**b;
	int		w_count;

	if (!s)
	{
		b = malloc(sizeof(char *));
		if (b == NULL)
			return (0);
		*b = 0;
		return (b);
	}
	while (*s == c && *s)
		s++;
	w_count = ft_wcount(s, c);
	b = malloc(sizeof(char *) * (w_count + 1));
	if (b == NULL)
		return (0);
	ft_strmalldup(b, s, c);
	b[w_count] = NULL;
	return (b);
}
