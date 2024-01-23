/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:46:49 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 20:15:50 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2, int b)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (b == 1)
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	if (b == 1)
	{
		res[i] = '/';
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	return (res[i] = '\0', res);
}
