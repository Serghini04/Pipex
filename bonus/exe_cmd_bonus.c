/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:55:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 20:12:18 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac)
{
	if (i == ac - 2)
	{
		if (dup2(data->write_fd, 1) == -1)
			(free_struct(data), perror("Dup error "), exit(1));
	}
	else if (dup2(data->fd[1], 1) == -1)
		(free_struct(data), perror("Dup error "), exit(1));
	close(data->write_fd);
	(close(data->fd[0]), close(data->fd[1]));
	if (execve(data->path_cmd, data->cmd, env) == -1)
	{
		free_struct(data);
		perror("Cmd not execute ");
		exit(1);
	}
}

void	here_doc_part(char **av, t_pipex *data)
{
	char	*read;
	char	*stop;

	stop = ft_strjoin(av[2], "\n", 0);
	data->read_fd = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->read_fd == -1)
		(free(data), perror("Open error "), exit(1));
	while (1)
	{
		write(1, "here_doc>>", 10);
		read = get_next_line(0);
		fprintf(stderr, ">>%s<<\n", read);
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
