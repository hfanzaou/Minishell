/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:50:26 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 23:38:44 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	a;
	int	sign;
	int	i;

	a = 0;
	i = 0;
	sign = 1;
	while (is_space(s[i]) && s[i])
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		a = a * 10 + (s[i] - 48);
		i++;
	}
	return (sign * a);
}
/*
int main(int ac, char **av)
{
	(void)ac;
	printf("%d\n", ft_atoi(av[1]));
}*/
