/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:21:04 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 02:21:13 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "token.h"

char	*ft_strjoin2(char const *s1, char const *s2, int n)
{
	int		i;
	int		j;
	char	*c;

	if (!s1 || !s2)
		return (NULL);
	i = strlen((char *)s1) + strlen((char *)s2);
	c = s_malloc(sizeof(char) * i + 1);
	if (c == NULL)
		return (0);
	j = 0;
	while (s1[j] && n)
	{
		c[j] = s1[j];
		n--;
		j++;
	}
	n = 0;
	while (s2[n])
	{
		c[j + n] = s2[n];
		n++;
	}
	c[j + n] = '\0';
	return (c);
}

int	ft_strrchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*b;

	c = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (c[i] != b[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup2(const char *s)
{
	char	*dst;
	char	*p;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dst = s_malloc(i * sizeof(char) + 1);
	if (dst == NULL)
		return (0);
	p = dst;
	while (*s)
	{
		*dst++ = *s++;
	}
	*dst = '\0';
	return (p);
}

int	ft_skip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (isalnum(str[i]) || !ft_strrchr("?_", str[i])))
		i++;
	return (i);
}
