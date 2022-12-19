/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:40:19 by hfanzaou          #+#    #+#             */
/*   Updated: 2021/11/17 17:22:43 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	b;

	if (!s)
		return ;
	b = '\n';
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	write(fd, &b, 1);
}
