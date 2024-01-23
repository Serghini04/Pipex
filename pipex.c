/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 16:29:18 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_run_cmd1(t_pipex *data, char **env)
{
	if (dup2(data->fd[1], 1) == -1)
		(free_struct(data), perror("Dup error "), exit(1));
	(close (data->write_fd), close(data->fd[1]), close(data->fd[0]));
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
			free_struct(data);
			(perror("Execve error "), exit(1));
		}
	}
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
	if (pipe(data->fd) == -1)
		(free_arr(path), free(data), perror("Pipe error "), exit(1));
	p = fork();
	if (p == -1)
		(free_struct(data), free_arr(path), perror("fork "), exit(1));
	if (p == 0)
	{
		parsing_arg(data, 2, av, path);
		child_run_cmd1(data, env);
	}
	else
		(parsing_arg(data, 3, av, path), run_cmd2(data, env));
	(free_struct(data), my_wait());
}
