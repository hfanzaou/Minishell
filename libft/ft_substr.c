/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:27:01 by ajana             #+#    #+#             */
/*   Updated: 2021/11/15 23:50:08 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s);
	if (start > (unsigned int)ft_strlen(s))
	{
		substr = ft_calloc(1, sizeof(char));
		if (!substr)
			return (NULL);
		return (substr);
	}
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

/*
int main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", ft_substr((const char *)av[1], atoi(av[2]), atoi(av[3])));
}*/
