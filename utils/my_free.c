/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:54:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/14 12:37:21 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_arr(char **res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

void	free_struct(t_pipex *data)
{
	if (data->path_cmd1)
		free(data->path_cmd1);
	if (data->path_cmd2)
		free(data->path_cmd2);
	if (data->cmd1 || *data->cmd1)
		free_arr(data->cmd1);
	if (data->cmd2 || *data->cmd2)
		free_arr(data->cmd2);
	free(data);
}
