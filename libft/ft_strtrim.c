/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:53:21 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 03:29:37 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	beg;
	size_t	end;

	if (!s1)
		return (NULL);
	beg = 0;
	end = ft_strlen((char *)s1);
	while (ft_strchr((char *)set, s1[beg]) && beg < end)
	{
		beg++;
	}
	while (ft_strchr((char *)set, s1[end - 1]) && end > beg)
	{
		end--;
	}
	s = (char *)malloc((end - beg + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1 + beg, end - beg + 1);
	return (s);
}
/*
int main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", ft_strtrim(av[1], av[2]));
}*/
