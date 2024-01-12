/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:05:13 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/12 19:06:00 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	i;
	int	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && needle[j] && (i + j) < len)
			j++;
		if (!needle[j])
			return (&(haystack)[i + j]);
		i++;
	}
	return (NULL);
}