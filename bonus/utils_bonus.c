/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:51:15 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/27 17:37:35 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	last_free(t_pipex *data, char *cmp)
{
	if (!ft_strcmp(cmp, "here_doc"))
		unlink("/tmp/my_f");
	my_close(data, 3);
	free(data);
}

void	open_close(t_pipex *data)
{
	data->read_fd = open("/tmp/my_f", O_RDONLY, 0644);
	if (data->read_fd == -1)
		(free(data), perror("Open error "), exit(1));
	if (dup2(data->read_fd, 0) == -1)
		(perror("Dup error "), free(data), exit(1));
	close(data->read_fd);
}

int	start(t_pipex *data)
{
	int	p;

	if (pipe(data->fd) == -1)
		(perror("Pipe error "), free(data), exit(1));
	p = fork();
	if (p == -1)
		(perror("fork error "), my_close(data, 0), free(data), exit(1));
	return (p);
}
