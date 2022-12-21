/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:29:18 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 22:52:22 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int main ()
{
	int src[] = {27845, 454346, 543543698};
	int dest[] = {1, 2, 2};
	//printf("%s\n", memcpy(dest, src, 2 * sizeof(char)));
	//printf("%s %s \n",dest, src);	
	ft_memcpy(dest, src, 3 * sizeof(int));
	for (int i = 0; i < 3; i++) 
		printf("%d %d \n", dest[i], src[i]);

}*/
