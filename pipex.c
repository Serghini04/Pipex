/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/17 23:24:32 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// this cmd for leaks fd system(lsof -c pipex);

void	child_run_cmd1(t_pipex *data, char **env)
{
	if (dup2(data->read_fd, 0) == -1 || dup2(data->fd[1], 1) == -1)
		(free_struct(data), perror("Dup error "), exit(1));
	(close (data->read_fd), close(data->fd[1]), close(data->fd[0]));
	if (execve(data->path_cmd, data->cmd, env) == -1)
	{
		free_struct(data);
		perror("Execve error ");
		exit(1);
	}
}

void	run_cmd2(t_pipex *data, char **env)
{
	int	p;

	p = fork();
	if (p == -1)
		(free_struct(data), perror("fork error "), exit(1));
	if (p == 0)
	{
		if (dup2(data->fd[0], 0) == -1 || dup2(data->write_fd, 1) == -1)
			(free_arr(data->cmd), perror("Dup error "), exit(1));
		(close(data->fd[0]), close(data->write_fd), close(data->fd[1]));
		if (execve(data->path_cmd, data->cmd, env) == -1)
		{
			(free(data->path_cmd), free_arr(data->cmd));
			(perror("Execve error "), exit(1));
		}
	}
	else
		data->pids[1] = p;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	char	**path;
	int		p;

	if (ac != 5 || !*env)
		return (perror("Arg error "), 0);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (1);
	path = first_part(data, ac, av, env);
	p = fork();
	if (p == -1)
		(free_struct(data), perror("fork error "), exit(1));
	if (p == 0)
	{
		parsing_arg(data, 2, av, path);
		child_run_cmd1(data, env);
	}
	else
	{
		data->pids[0] = p;
		parsing_arg(data, 3, av, path);
		run_cmd2(data, env);
	}
	my_close(data);
	waitpid(data->pids[1], 0, 0);
	waitpid(data->pids[0], 0, 0);
	return (0);
}
