/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <hfanzaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:54:04 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/29 03:19:21 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*remove_spaces(char *str)
{
	int		i;
	char	*ret;
	char	*c;

	i = 0;
	c = ft_strdup2(" ");
	ret = ft_strdup2("");
	while (str[i])
	{
		c[0] = str[i];
		c[1] = '\0';
		if (ft_strrchr(" \t", str[i]))
			ret = ft_strjoin2(ret, c, strlen(ret));
		else if (ret[0] && !ft_strrchr(" \t", str[i])
			&& str[i + 1] && ft_strrchr(" \t", str[i + 1]))
			ret = ft_strjoin2(ret, " ", strlen(ret));
		i++;
	}
	return (ret);
}

char	*compare_exp(char *s, int j)
{
	t_envlist	*tmp;

	tmp = g_global.envlist;
	while (tmp)
	{
		if (!ft_memcmp(tmp->key, s, ft_strlen(tmp->key)))
		{
			if (j == 2)
				return (tmp->value);
			else if (j <= 2)
				return (remove_spaces(tmp->value));
		}
		tmp = tmp->next;
	}
	return ("\0");
}

char	*ft_expand(char *val, t_lexer **lexer, int j)
{
	char	*s;
	int		l;

	l = 1;
	if (!val)
		return (NULL);
	if (val[1] == '?')
	{
		lexer_advance(lexer);
		if (WIFEXITED(g_global.exit_status))
			return ((ft_itoa2(WEXITSTATUS(g_global.exit_status))));
		else
			return ((ft_itoa2(WTERMSIG(g_global.exit_status) + 128)));
	}
	while (val[l] && (isalnum(val[l]) || val[l] == '_'))
	{
		if (j == 1)
			lexer_advance(lexer);
		l++;
	}
	s = compare_exp(&val[1], j);
	if (!s[0])
		(*lexer)->f = 1;
	return (s);
}
