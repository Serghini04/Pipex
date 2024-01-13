/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:25:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 12:29:22 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	count_word(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word(char *s, char c)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && s[len] != c)
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	free_split(char **res, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char	**split_string(char const *s, char c, int word_count)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			res[i] = get_word((char *)s, c);
			if (!res[i])
				return (free_split(res, i), NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int	word_count;

	if (!s)
		return (NULL);
	word_count = count_word((char *)s, c);
	return (split_string(s, c, word_count));
}
