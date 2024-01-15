/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/15 18:00:32 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_split_path(char **env)
{
	int		i;
	char	*path;
	char	**res;

	i = 0;
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
	if (!data->read_fd || !data->write_fd)
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->write_fd == -1)
			return (perror("Open error "), 0);
		data->read_fd = open(av[1], O_RDONLY);
		if (data->read_fd == -1)
			return (perror("Open error "), 0);
	}
	return (1);
}

t_pipex	*parsing_arg(int ac, char **av, char **env)
{
	t_pipex	*data;
	char	**path;

	if (ac != 5 || !*env)
		return (perror("Arg error "), NULL);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (NULL);
	if (open_file(data, ac, av) == 0)
		return (free(data), perror("Open error "), NULL);
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	if (!data->cmd1 || !data->cmd2)
		return (free_struct(data), perror("Split error "), NULL);
	path = find_split_path(env);
	if (!path)
		return (free_struct(data), perror("Split error "), NULL);
	data->path_cmd1 = checker_cmd(data->cmd1[0], path);
	data->path_cmd2 = checker_cmd(data->cmd2[0], path);
	if (!data->path_cmd1 || !data->path_cmd2)
		return (free_struct(data), free_arr(path), perror("Cmd error "), NULL);
	if (pipe(data->fd) == -1)
		return (free_struct(data), free_arr(path), perror("Pipe error "), NULL);
	return (free_arr(path), data);
}
