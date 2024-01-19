/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:54:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/19 15:23:09 by meserghi         ###   ########.fr       */
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

void	my_close(t_pipex *data)
{
	if (data->read_fd != -1)
		close(data->read_fd);
	if (data->write_fd != -1)
		close(data->write_fd);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	free_struct(t_pipex *data)
{
	free_arr(data->cmd);
	free(data->path_cmd);
	my_close(data);
	free(data->pids);
	free(data);
}

void	my_wait(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->pos)
	{
		if (waitpid(data->pids[i++], 0, 0) == -1)
			exit(1);
	}
}
