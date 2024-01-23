/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 22:10:44 by meserghi         ###   ########.fr       */
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
	while (path[i])
	{
		res = ft_strjoin(path[i], str, 1);
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

int	open_file(t_pipex *data, int ac, char **av, int b)
{
	if (b == 1)
	{
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->write_fd == -1)
			return (my_close(data), perror("Open error "), 0);
	}
	else
	{
		data->read_fd = open(av[1], O_RDONLY);
		data->write_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->read_fd == -1 || data->write_fd == -1)
			return (my_close(data), perror("Open error"), 0);
	}
	return (1);
}

void	parsing_arg(t_pipex *data, int i, char **av, char **env)
{
	char	**path;

	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd || !*data->cmd)
		perror("Cmd error ");
	if (access(data->cmd[0], F_OK | X_OK) == 0)
	{
		data->path_cmd = ft_strdup(data->cmd[0]);
		return ;
	}
	else
	{
		path = find_split_path(env);
		if (!path)
			(free(data), my_close(data), perror("Split error "), exit(1));
		data->path_cmd = checker_cmd(data->cmd[0], path);
		if (!data->path_cmd)
			perror("Cmd error ");
		free_arr(path);
	}
}

t_pipex	*first_part(int ac, char **av, int b, char **env)
{
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
		(perror("malloc error "), exit(1));
	if (open_file(data, ac, av, b) == 0)
		(free(data), exit(1));
	data->env = env;
	return (data);
}
