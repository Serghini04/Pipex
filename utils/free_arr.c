/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:54:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 17:48:56 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_arr(char **res)
{
	int	i;

	i = 0;
	if (!res || !*res)
		return ;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

void	free_all_arr(char **s1, char **s2, char **s3)
{
	free_arr(s1);
	free_arr(s2);
	free_arr(s3);
}