/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:55:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/18 15:57:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac)
{
	if (i == 2)
	{
		if (dup2(data->read_fd, 0) == -1)
			(perror("Dup error "), exit(1));
		close(data->read_fd);
	}
	if (i == ac - 2)
	{
		if (dup2(data->write_fd, 1) == -1)
			(perror("Dup error "), exit(1));
		close(data->write_fd);
	}
	else if (dup2(data->fd[1], 1) == -1)
		(perror("Dup error "), exit(1));
	(close(data->fd[1]), close(data->fd[0]));
	if (execve(data->path_cmd, data->cmd, env) == -1)
	{
		perror("Execve error ");
		exit(1);
	}
}
