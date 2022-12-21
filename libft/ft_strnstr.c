/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:06:42 by ajana             #+#    #+#             */
/*   Updated: 2021/11/12 22:01:07 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
				return (&((char *)haystack)[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
/*
int main (int ac, char **av)
{
	(void)ac;
	printf("miine >> %s\n",ft_strnstr(av[1],av[2],ft_atoi(av[3])));
	printf("origin >> %s\n",strnstr(av[1],av[2],ft_atoi(av[3])));
}*/
