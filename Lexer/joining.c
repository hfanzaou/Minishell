/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:13:47 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/12/28 05:13:48 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "token.h"

char 	*to_join(char c)
{
	char *str;

	str = ft_strdup2(" ");
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char 	*dq_case(t_lexer *lexer, char **env)
{
	char *str;
	char *val;
	int i;

	i = 0;
	str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
	if (!str)
		return(NULL);
	val = ft_strdup2("");
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || !ft_strrchr("?_", str[i + 1])))
		{
			val = ft_strjoin2(val, ft_expand(&str[i], env, &lexer, 2), ft_strlen(val));
			i += ft_skip(&str[i + 1]);
		}
		else
			val = ft_strjoin2(val, to_join(str[i]), ft_strlen(val));
		i++;
	}
	return (val);
}

char	*join_expand(t_lexer *lexer, char *val, char *val2, char **env)
{
	char *str;

	str = ft_expand(val2, env, &lexer, 1);
	lexer_advance(&lexer);
	str = ft_strjoin2(val, str, ft_strlen(val));
	return (str);
 }

 char	*just_join(t_lexer *lexer, char *val, char *c)
 {
	char *str;

	if (c[0])
	{
		str = ft_strjoin2(val, c, ft_strlen(val));
		// free(c);
		lexer_advance(&lexer);
	}
	else if (!c[0] && lexer->c == '\"')
	{
		str = dq_case(lexer, global.envp);
		str = ft_strjoin2(val, str, ft_strlen(val));
	}
	else 
	{
		str = remove_quotes(lexer->c, lexer, &lexer->src[lexer->i]);
		str = ft_strjoin2(val, str, ft_strlen(val));
	}
	if (!str)
		return (NULL);
	return (str);
 }