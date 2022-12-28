/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:54:04 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 04:54:09 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*remove_spaces(char *str)
{
	int i;
	char *ret;
	char *c;
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

char 	*compare_exp(int l, char **env, char *s, int j)
{
	int i;
	i = 0;
	while (env[i])
	{
		if (!ft_memcmp(env[i], s, l - 1) && env[i][l - 1] && env[i][l - 1] == '=')
		{
			if (j == 2)
				return (&env[i][l]);	
			else if (j <= 2)
				return (remove_spaces(&env[i][l]));
		}
		i++;
	}
	return ("\0");
}

char	*ft_expand(char *val, char **env, t_lexer **lexer, int j)
{
	char *s;
	int l;
	char	*s1;
	l = 1;
	s = val;
	if (!s)
		return NULL;
	if (s[1] == '?')
	{
		lexer_advance(lexer);	
		return ((ft_itoa2(WEXITSTATUS(global.exit_status))));
	}
	while (s[l] && (isalnum(s[l]) || s[l] == '_'))
	{
		if (j == 1)
			lexer_advance(lexer);
		l++;
	}
	s1 = compare_exp(l, env, &s[1], j);
	if (!s1[0])
		(*lexer)->f = 1;
	return (s1);
}
