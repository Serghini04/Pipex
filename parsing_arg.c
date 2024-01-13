/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 22:03:45 by meserghi         ###   ########.fr       */
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

int	if_valid_cmd(char **cmd, char **path)
{
	char	*cmd_path;

	cmd_path = checker_cmd(cmd[0], path);
	if (!cmd_path)
		return (0);
	free(cmd_path);
	return (1);
}

t_pipex	*parsing_arg(int ac, char **av, char **env)
{
	t_pipex	*data;
	char	**path;

	if (ac != 5)
		return (perror("Arg error "), NULL);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (NULL);
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	if (!data->cmd1 || !*data->cmd1 || !data->cmd2 || !*data->cmd2)
		return (free_struct(data), perror("Split error "), NULL);
	path = find_split_path(env);
	if (!path)
		return (free_struct(data), perror("Split error "), NULL);
	data->read_fd = open(av[1], O_RDWR);
	if (data->read_fd == -1)
		return (free_struct(data), free_arr(path), perror("Open error "), NULL);
	data->path_cmd1 = checker_cmd(data->cmd1[0], path);
	data->path_cmd2 = checker_cmd(data->cmd2[0], path);
	if (!data->path_cmd1 || !data->path_cmd2)
		return (free_struct(data), free_arr(path), perror("Cmd error "), NULL);
	if (pipe(data->fd) == -1)
		return (free_struct(data), free_arr(path), perror("Pipe error "), NULL);
	return (free_arr(path), data);
}
