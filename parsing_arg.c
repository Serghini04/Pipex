/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 17:46:06 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_split_path(char **env)
{
	int		i;
	int		j;
	char	*path;
	char	**res;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
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

char	**parsing_arg(int ac, char **av, char **env)
{
	char	**path;
	char	**cmd1;
	char	**cmd2;

	if (ac != 5)
		return (perror("Arg error "), NULL);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	if (!cmd1 || !cmd2)
		return (free_all_arr(cmd1, cmd2, NULL), perror("Split error "), NULL);
	path = find_split_path(env);
	if (!path)
		return (free_all_arr(cmd1, cmd2, NULL), perror("Split error "), NULL);
	else if (open(av[1], O_RDWR) == -1)
		return (free_all_arr(cmd1, cmd2, path), perror("Open error "), NULL);
	else if (!if_valid_cmd(cmd1 , path) || !if_valid_cmd(cmd2, path))
		return (free_all_arr(cmd1, cmd2, path), NULL);
	free_all_arr(cmd1, cmd2, NULL);
	return (path);
}
