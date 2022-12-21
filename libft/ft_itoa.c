/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <ajana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:09:19 by ajana             #+#    #+#             */
/*   Updated: 2021/11/17 23:31:03 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(unsigned int nu)
{
	int	i;

	i = 1;
	while (nu > 9)
	{
		nu = nu / 10;
		i++;
	}
	return (i);
}

char	*assign(char *str, unsigned int n, int sign)
{
	int	i;

	i = int_len(n) + sign - 1;
	if (sign)
		*str = '-';
	while (n > 9)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	str[i] = n + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nu;
	char			*res;
	int				sign;
	int				len;

	sign = 0;
	if (n < 0)
	{
		nu = n * -1;
		sign = 1;
	}
	else
		nu = n;
	len = int_len(nu);
	res = malloc((len + 1 + sign) * sizeof(char));
	if (!res)
		return (NULL);
	res[len + sign] = '\0';
	return (assign(res, nu, sign));
}

/*
int	main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", ft_itoa(ft_atoi(av[1])));
}*/
