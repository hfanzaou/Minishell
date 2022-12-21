/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:23:46 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 23:27:11 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, sizeof(char));
}
/*
int main()
{
	int fd;
	int fd1;
	
	fd1 = open("o", O_CREAT | O_WRONLY, 007700);
	fd = open("k", O_CREAT | O_WRONLY, 007700);
	printf("%d\n", fd);
	printf("%d\n", fd1);
	ft_putchar_fd('c', fd1);

}*/
