/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:01:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 21:13:33 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_bonus(t_pipex *data)
{
	free_arr(data->cmd);
	free(data->path_cmd);
}

void	last_free(t_pipex *data)
{
	my_close(data);
	unlink("/tmp/my_f");
	free(data);
}

void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **env)
{
	char	**path;

	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd)
		(perror("Cmd error 1"), exit(1));
	if (access(data->cmd[0], F_OK | X_OK) == 0)
		data->path_cmd = ft_strdup(data->cmd[0]);
	else
	{
		path = find_split_path(env);
		if (!path)
			(free(data), my_close(data), perror("Split error "), exit(1));
		data->path_cmd = checker_cmd(data->cmd[0], path);
		if (!data->path_cmd)
			(perror("Cmd error "), exit(1));
		free_arr(path);
	}
}

void	part_exe_cmd(t_pipex *data, char **av, int i, int ac)
{
	int	p;

	if (pipe(data->fd) == -1)
		(perror("Pipe error "), exit(1));
	p = fork();
	if (p == -1)
		(exit(1));
	if (p == 0)
	{
		parsing_arg_bonus(data, i, av, data->env);
		child_run_cmd1_bonus(data, data->env, i, ac);
	}
	else
	{
		free_bonus(data);
		if (dup2(data->fd[0], 0) == -1)
			(perror("Dup error "), exit(1));
		(close(data->fd[0]), close(data->fd[1]));
	}
}

void f()
{
	system("leaks pipex_bonus");
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	int		i;

	i = 2;
	if (ac < 5 || !*env)
		return (perror("Arg error "), 1);
	if (!ft_strcmp("here_doc", av[1]))
	{
		data = first_part(ac, av, 1, env);
		here_doc_part(av, data);
		i = 3;
	}
	else
		data = first_part(ac, av, 0, env);
	if (dup2(data->read_fd, 0) == -1)
		(free(data), perror("Dup error "), exit(1));
	close(data->read_fd);
	while (i <= ac - 2)
	{
		part_exe_cmd(data, av, i, ac);
		i++;
	}
	atexit(f);
	my_wait();
	last_free(data);
	return (0);
}
