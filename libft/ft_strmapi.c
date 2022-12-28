/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:43:35 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/21 01:35:19 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*l;

	if (!s)
		return (0);
	i = ft_strlen((char *)s);
	l = malloc(sizeof(char) * (i + 1));
	if (l == NULL)
		return (0);
	i = 0;
	if (*s && *f)
	{
		while (s[i])
		{
			l[i] = f(i, s[i]);
			i++;
		}
	}
	l[i] = '\0';
	return (l);
}
