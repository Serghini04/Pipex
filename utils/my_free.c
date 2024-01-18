/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:54:51 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/18 13:15:34 by meserghi         ###   ########.fr       */
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
	if (data->path_cmd)
		free(data->path_cmd);
	if (data->cmd || *data->cmd)
		free_arr(data->cmd);
	if (data->pids)
		free(data->pids);
	free(data);
}

void	my_wait(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->pos)
		waitpid(data->pids[i++], 0, 0);
}