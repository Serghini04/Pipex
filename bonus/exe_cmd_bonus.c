/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:55:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 17:40:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac)
{
	if (i != ac - 2)
	{
		if (dup2(data->fd[1], 1) == -1)
			(free_struct(data, 2), perror("Dup error "), exit(1));
	}
	my_close(data, 0);
	if (execve(data->path_cmd, data->cmd, env) == -1)
	{
		free_struct(data, 2);
		perror("Cmd not execute ");
		exit(1);
	}
}

void	open_file(t_pipex *data, int ac, char **av, char *check)
{
	if (!ft_strcmp(check, "here_doc"))
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->write_fd == -1)
			(perror("Open error "), my_close(data, 2), free(data), exit(1));
	}
	else
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->write_fd == -1)
			(perror("Open error "), my_close(data, 2), free(data), exit(1));
	}
	if (dup2(data->write_fd, 1) == -1)
		(perror("dup error "), my_close(data, 2), free(data), exit(1));
	close(data->write_fd);
}

void	here_doc_part(char **av, t_pipex *data)
{
	char	*read;
	char	*stop;

	data->read_fd = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->read_fd == -1)
		(free(data), perror("Open error "), exit(1));
	stop = ft_strjoin(av[2], "\n", 0);
	while (1)
	{
		write(1, "here_doc>>", 10);
		read = get_next_line(0);
		if (!ft_strcmp(read, stop))
		{
			free(read);
			break ;
		}
		write(data->read_fd, read, ft_strlen(read));
		free(read);
	}
	free(stop);
	close(data->read_fd);
	data->read_fd = open("/tmp/my_f", O_RDONLY, 0644);
	if (data->read_fd == -1)
		(free(data), perror("Open error "), exit(1));
}
