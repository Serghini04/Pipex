/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 22:44:59 by meserghi         ###   ########.fr       */
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

void	child_run_cmd2(t_pipex *data, char *name_oufile, char **env)
{
	data->write_fd = open(name_oufile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->write_fd == -1)
		(perror("Open error "), exit(1));
	if (dup2(data->fd[0], 0) == -1 || dup2(data->write_fd, 1) == -1)
		(free_arr(data->cmd2), perror("Dup error "), exit(1));
	(close(data->fd[0]), close(data->write_fd), close(data->fd[1]));
	if (execve(data->path_cmd2, data->cmd2, env) == -1)
	{
		(free(data->path_cmd2), free_arr(data->cmd2));
		(perror("Execve error "), exit(1));
	}
}

void f()
{
	system("leaks pipex");
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	int		p;

	atexit(f);
	data = parsing_arg(ac, av, env);
	if (!data)
		return (1);
	p = fork();
	if (p == -1)
		return (free_struct(data), perror("fork error "), 1);
	if (p == 0)
		child_run_cmd1(data, env);
	else
	{
		p = fork();
		if (p == -1)
			(free_struct(data), perror("fork error "), exit(1));
		if (p == 0)
			child_run_cmd2(data, av[4], env);
		wait(0);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	free_struct(data);
	return (0);
}
