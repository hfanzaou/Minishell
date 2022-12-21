/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:50:48 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 21:44:40 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nu;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nu = n * -1;
	}
	else
		nu = n;
	if (nu > 9)
	{
		ft_putnbr_fd(nu / 10, fd);
	}
	ft_putchar_fd((nu % 10) + 48, fd);
}
/*
#include <fcntl.h>
int main (int ac, char **av)
{
	int	fd;

	(void)ac;
	fd = open(av[1], O_CREAT | O_WRONLY, 777);
	ft_putnbr_fd(ft_atoi(av[2]), fd);
}*/
