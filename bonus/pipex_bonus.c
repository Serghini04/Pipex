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

#include "../pipex.h"

void	my_wait(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->pos)
		waitpid(data->pids[i++], 0, 0);
}
void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **path)
{
	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd || !*data->cmd)
		(free_struct(data), perror("Split error "), exit(1));
	data->path_cmd = checker_cmd(data->cmd[0], path);
	if (!data->path_cmd)
		(free_struct(data), free_arr(path), perror("Cmd error "), my_wait(data), exit(1));
	if (pipe(data->fd) == -1)
		(free_struct(data), free_arr(path), perror("Pipe error "), my_wait(data), exit(1));
}

void	part_exe_cmd(t_pipex *data, char **env, int i, int ac)
{
	int  p;

	p = fork();

	if ( p == -1)
		(free_struct(data), exit(1));
	if (p == 0)
		child_run_cmd1_bonus(data, env, i, ac);
	else
		data->pids[i - 2] = p;
	free_struct(data);
}

int main(int ac, char **av, char **env)
{
	t_pipex *data;
	char	**path;
	int 	i = 2;

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
		close(data->fd[0]);
		i++;
	}
	i = -1;
	my_wait(data);
	free_arr(path);
	free(data->pids);
	free(data);
	(close(data->read_fd), close(data->write_fd));
	return (0);
}
