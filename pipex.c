/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 16:03:03 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_run_cmd1(t_pipex *data, char **env)
{
	if (dup2(data->fd[1], 1) == -1 || dup2(data->read_fd, 0) == -1)
		(free_struct(data, 2), perror("Dup error "), exit(1));
	my_close(data, 2);
	if (execve(data->path_cmd, data->cmd, env) == -1)
	{
		free_struct(data, 2);
		perror("Execve error ");
		exit(1);
	}
}

void	run_cmd2(t_pipex *data, char **env)
{
	int	p;

	p = fork();
	if (p == -1)
		(free_struct(data, 3), perror("fork error "), exit(1));
	if (p == 0)
	{
		if (dup2(data->fd[0], 0) == -1 || dup2(data->write_fd, 1) == -1)
			(free_struct(data, 3), perror("Dup error "), exit(1));
		my_close(data, 3);
		if (execve(data->path_cmd, data->cmd, env) == -1)
		{
			free_struct(data, 3);
			(perror("Execve error "), exit(1));
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	int		p;

	data = first_part(ac, env, &p);
	if (p == 0)
	{
		data->read_fd = open(av[1], O_RDONLY);
		if (data->read_fd == -1)
			return (perror("Open error "), my_close(data, 0), free(data), 1);
		parsing_arg(data, 2, av, env);
		child_run_cmd1(data, env);
	}
	else
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->write_fd == -1)
			return (perror("Open error "), my_close(data, 0), free(data), 1);
		(parsing_arg(data, 3, av, env), run_cmd2(data, env));
	}
	(free_struct(data, 3), my_wait());
}
