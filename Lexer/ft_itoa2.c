/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:59:12 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 14:31:23 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*retreive_key(char *str)
{
	char	*search;

	search = ft_strchr(str, '=');
	if (search)
		return (ft_strdup(search + 1));
	else
		return (NULL);
}

int	ft_ret(char *args)
{
	ft_error("minishell: export: `", args, "': not a valid identifier\n");
	return (256);
}

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

char	*ft_itoa2(int n)
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
	res = s_malloc((len + 1 + sign) * sizeof(char));
	if (!res)
		return (NULL);
	res[len + sign] = '\0';
	return (assign(res, nu, sign));
}
