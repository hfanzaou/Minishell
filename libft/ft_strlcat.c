/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:00:25 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 21:09:47 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	i = dstlen;
	j = 0;
	if (dstsize > dstlen)
	{
		while (src[j] && i < dstsize - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (dstlen + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}
/*
int main (int ac, char **av)
{
	(void)ac;
	char dst[10] = "hell";
	//printf("%lu \n", ft_strlcat(dst, "maza", 0));
	printf("%lu \n", ft_strlcat(dst, 0, 10));
	printf("%s\n", dst);
}*/
