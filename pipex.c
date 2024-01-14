/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/14 23:23:04 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_run_cmd1(t_pipex *data, char **env)
{
	if (dup2(data->read_fd, 0) == -1 || dup2(data->fd[1], 1) == -1)
		(free_struct(data), perror("Dup error "), exit(1));
	(close (data->read_fd), close(data->fd[1]), close(data->fd[0]));
	if (execve(data->path_cmd1, data->cmd1, env) == -1)
	{
		free_struct(data);
		perror("Execve error ");
		exit(1);
	}
}

void	child_run_cmd2(t_pipex *data, char **env)
{
	if (dup2(data->fd[0], 0) == -1 || dup2(data->write_fd, 1) == -1)
		(free_arr(data->cmd2), perror("Dup error "), exit(1));
	(close(data->fd[0]), close(data->write_fd), close(data->fd[1]));
	if (execve(data->path_cmd2, data->cmd2, env) == -1)
	{
		(free(data->path_cmd2), free_arr(data->cmd2));
		(perror("Execve error "), exit(1));
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	int		p;

	data = parsing_arg(ac, av, env);
	if (!data)
		return (1);
	p = fork();
	if (p == -1)
		(free_struct(data), perror("fork error "), exit(1));
	if (p == 0)
		child_run_cmd1(data, env);
	else
	{
		p = fork();
		if (p == -1)
			(free_struct(data), perror("fork error "), exit(1));
		if (p == 0)
			child_run_cmd2(data, env);
	}
	(close(data->fd[0]), close(data->fd[1]));
	free_struct(data);
	(wait(0), wait(0));
	return (0);
}
