/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 16:39:55 by meserghi         ###   ########.fr       */
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

void	parsing_arg(t_pipex *data, int i, char **av, char **env)
{
	char	**path;

	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd || !*data->cmd)
		(perror("Cmd error "), my_close(data, i), free(data), exit(1));
	if (access(data->cmd[0], F_OK | X_OK) == 0)
	{
		data->path_cmd = ft_strdup(data->cmd[0]);
		return ;
	}
	else
	{
		path = find_split_path(env);
		if (!path)
			(free_arr(data->cmd), my_close(data, i), perror("path "), exit(1));
		data->path_cmd = checker_cmd(data->cmd[0], path);
		if (!data->path_cmd)
		{
			perror("Cmd error ");
			(free_arr(path), free_struct(data, i), exit(1));
		}
		free_arr(path);
	}
}

t_pipex	*first_part(int ac, char **env, int *p)
{
	t_pipex	*data;

	if (ac != 5 || !*env)
		(perror("Arg error "), exit(1));
	data = malloc(sizeof(t_pipex));
	if (!data)
		(perror("malloc error "), exit(1));
	if (pipe(data->fd) == -1)
		(free(data), perror("Pipe error "), exit(1));
	*p = fork();
	if (*p == -1)
		(free(data), perror("fork error "), exit(1));
	data->env = env;
	return (data);
}
