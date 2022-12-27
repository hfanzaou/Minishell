/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajana <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:06:53 by ajana             #+#    #+#             */
/*   Updated: 2021/11/16 17:17:12 by ajana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	words_num(char const *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
			while (*s == c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	**ft_free(char **str, int i)
{
	if (!str)
		return (NULL);
	i--;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		words;
	int		len;
	int		i;

	i = 0;
	words = words_num(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < words)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		res[i] = malloc((len + 1) * sizeof(char));
		if (!res[i])
			return (ft_free(&res[i], i));
		ft_strlcpy(res[i], s, len + 1);
		s += len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
/*
int    main()
{
    char const s[] = "//zack///is/here////";
    char *string = "      split       this for   me  !       ";
    char c = ' ';
    int i = 0;
    char str;
    str = ft_split(string, c);
    for (; i < 6; i++)
        printf("%s\n", str[i]);

}*/
