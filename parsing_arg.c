/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 12:07:11 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_split_path(char **env)
{
	int		i;
	char	*path;
	char	**res;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strnstr(env[i], "PATH=", 5);
			break ;
		}
		i++;
	}
	res = ft_split(path, ':');
	return (res);
}

char	*checker_cmd(char *str, char **path)
{
	int		i;
	char	*res;

	i = 0;
	if (if_are_path(str) == 1)
		return (ft_strdup(str));
	while (path[i])
	{
		res = ft_strjoin(path[i], str);
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

int	open_file(t_pipex *data, int ac, char **av)
{
	if (!ft_strncmp("here_doc", av[1], 8))
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->write_fd == -1)
			return (my_close(data), perror("Open error"), 0);
		return (1);
	}
	data->read_fd = open(av[1], O_RDONLY);
	data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->read_fd == -1 || data->write_fd == -1)
		return (my_close(data), perror("Open error"), 0);
	return (1);
}

void	parsing_arg(t_pipex *data, int i, char **av, char **path)
{
	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd || !*data->cmd)
		perror("Cmd error ");
	exit(1);
	data->path_cmd = checker_cmd(data->cmd[0], path);
	if (!data->path_cmd)
		perror("Cmd error ");
	free_arr(path);
}

char	**first_part(t_pipex *data, int ac, char **av, char **env)
{
	char	**path;

	if (open_file(data, ac, av) == 0)
		(free(data), exit(1));
	if (dup2(data->read_fd, 0) == -1)
		(free(data), perror("Dup error "), exit(1));
	close(data->read_fd);
	path = find_split_path(env);
	if (!path)
		(free(data), my_close(data), perror("Split error "), exit(1));
	return (path);
}
