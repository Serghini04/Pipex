 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:01:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/14 22:32:27 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*parsing_arg_bonus(int ac, int i, char **av, char **env)
{
	t_pipex	*data;
	char	**path;

	if (ac < 5 || !*env)
		return (perror("Arg error "), NULL);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (NULL);
	if (open_file(data, ac, av) == 0)
		return (free(data), perror("Open error "), NULL);
	data->cmd1 = ft_split(av[i], ' ');
	data->cmd2 = ft_split(av[i + 1], ' ');
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

int main(int ac, char **av, char **env)
{
	t_pipex *data;
	int save_read;
	int	i = 1;

	while (i < ac - 2)
	{
		data = parsing_arg_bonus(ac, i, av, env);
		if (!data)
			return (0);
	}
}