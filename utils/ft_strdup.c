/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:12:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/15 12:38:24 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(char *s1)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
