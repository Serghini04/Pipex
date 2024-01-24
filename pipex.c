/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/24 16:54:33 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_run_cmd1(t_pipex *data, char **env)
{
	if (dup2(data->fd[1], 1) == -1 || dup2(data->read_fd, 0) == -1)
		(free_struct(data), perror("Dup error "), exit(1));
	my_close(data);
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
			(free_struct(data), perror("Dup error "), exit(1));
		my_close(data);
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
	int		p;

	if (ac != 5 || !*env)
		return (perror("Arg error "), 0);
	data = first_part(ac, av, 0, env);
	if (pipe(data->fd) == -1)
		(my_close(data), free(data), perror("Pipe error "), exit(1));
	p = fork();
	if (p == -1)
		(my_close(data), free(data), perror("fork error "), exit(1));
	if (p == 0)
	{
		parsing_arg(data, 2, av, env);
		child_run_cmd1(data, env);
	}
	else
		(parsing_arg(data, 3, av, env), run_cmd2(data, env));
	(free_struct(data), my_wait());
}
