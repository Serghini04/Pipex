/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:01:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/18 22:53:33 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void free_bonus(t_pipex *data)
{
	if (data->cmd)
		free_arr(data->cmd);
	if (data->path_cmd)
		free(data->path_cmd);
}

void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **path)
{
	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd || !*data->cmd)
		(perror("Cmd error "), free_struct(data), my_wait(data), exit(1));
	data->path_cmd = checker_cmd(data->cmd[0], path);
	if (!data->path_cmd)
		(perror("Cmd error "), free_struct(data), my_wait(data), exit(1));
	if (pipe(data->fd) == -1)
		(perror("Pipe error "), free_struct(data), my_wait(data), exit(1));
}

void	part_exe_cmd(t_pipex *data, char **env, int i, int ac)
{
	int  p;

	p = fork();

	if ( p == -1)
		(exit(1));
	if (p == 0)
		child_run_cmd1_bonus(data, env, i, ac);
	else
		data->pids[i - 2] = p;
	free_bonus(data);
}

void f()
{
	system("leaks pipex_bonus");
}

int main(int ac, char **av, char **env)
{
	t_pipex *data;
	char	**path;
	int 	i = 2;
	atexit(f);
	if (ac <= 5 || !*env)
		return (perror("Arg error "), 1);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (1);
	path = first_part(data, ac, av, env);
	while (i <= ac - 2)
	{
		parsing_arg_bonus(data, i, av, path);
		part_exe_cmd(data, env, i, ac);
		dup2(data->fd[0], 0);
		(close(data->fd[0]), close(data->fd[1]));
		i++;
	}
	free(data->pids);
	my_wait(data);
	free_arr(path);
	my_close(data);
	free(data);
	return (0);
}
