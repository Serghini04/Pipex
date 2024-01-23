/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:58:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 10:43:12 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_read(int fd, char *res)
{
	char	*buff;
	int		size;

	if (!res)
	{
		res = malloc(1 * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
	}
	size = 1;
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (free(res), NULL);
	while (size > 0 && !ft_check(res))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
			return (free(buff), free(res), NULL);
		buff[size] = '\0';
		res = ft_str_join(res, buff);
	}
	return (free(buff), res);
}

char	*clean_res(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	return (res[i] = '\0', res);
}

char	*next_line(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	res = malloc((ft_str_len(str) - i + 1) * sizeof(char));
	if (!res)
		return (free(str), NULL);
	i++;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*save_res;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save_res = ft_get_read(fd, save_res);
	if (!save_res)
		return (NULL);
	res = clean_res(save_res);
	if (!res)
		return (free(save_res), save_res = NULL, NULL);
	save_res = next_line(save_res);
	return (res);
}
