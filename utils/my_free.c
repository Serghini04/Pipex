/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:54:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 15:50:13 by meserghi         ###   ########.fr       */
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
	res = NULL;
}

void	my_close(t_pipex *data, int i)
{
	if (i == 2)
		close(data->read_fd);
	else if (i == 3)
		close(data->write_fd);
	else if (i == 1)
	{
		close(data->read_fd);
		close(data->write_fd);
	}
	close(data->fd[0]);
	close(data->fd[1]);
}

void	free_struct(t_pipex *data , int i)
{
	if (data->cmd)
		free_arr(data->cmd);
	if (data->path_cmd)
		free(data->path_cmd);
	my_close(data, i);
	free(data);
}

void	my_wait(void)
{
	while (wait(0) != -1)
		;
}
