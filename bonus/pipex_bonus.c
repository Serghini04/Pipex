/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:01:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 17:41:04 by meserghi         ###   ########.fr       */
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
	my_close(data, 3);
	unlink("/tmp/my_f");
	free(data);
}

void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **env)
{
	char	**path;

	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd)
		(perror("Cmd error 1"), close(data->read_fd), free(data), exit(1));
	if (access(data->cmd[0], F_OK | X_OK) == 0)
		data->path_cmd = ft_strdup(data->cmd[0]);
	else
	{
		path = find_split_path(env);
		if (!path)
			(my_close(data, 0), free(data), perror("path error "), exit(1));
		data->path_cmd = checker_cmd(data->cmd[0], path);
		if (!data->path_cmd)
			(perror("Cmd error "), free_bonus(data), exit(1));
		free_arr(path);
	}
}

void	part_exe_cmd(t_pipex *data, char **av, int i, int ac)
{
	int	p;

	if (pipe(data->fd) == -1)
		(perror("Pipe error "), close(data->read_fd), free(data), exit(1));
	p = fork();
	if (p == -1)
		(perror("fork error "), close(data->read_fd), free(data), exit(1));
	if (p == 0)
	{
		if (i == ac - 2)
			open_file(data, ac, av, av[1]);
		else if (i == 2)
		{
			data->read_fd = open(av[1], O_RDONLY);
	    	if (data->read_fd == -1 || data->write_fd == -1)
				(perror("Open error "), free(data), exit(1));
			dup2(data->read_fd, 0);
			close(data->read_fd);
		}
		parsing_arg_bonus(data, i, av, data->env);
		child_run_cmd1_bonus(data, data->env, i, ac);
	}
	else
	{
		if (dup2(data->fd[0], 0) == -1)
			(perror("Dup error "), exit(1));
		(close(data->fd[0]), close(data->fd[1]));
	}
}

t_pipex	*first_part_bonus(int ac, char **av, char **env, int *i)
{
	t_pipex	*data;

	if (ac < 5 || !*env)
		(perror("Arg error "), exit(1));
	data = malloc(sizeof(t_pipex));
	if (!data)
		(perror("malloc error "), exit(1));
	if (!ft_strcmp("here_doc", av[1]))
	{
		here_doc_part(av, data);
		*i = 3;
	}
	else
		*i = 2;
	data->env = env;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	int		i;

	i = 2;
	data = first_part_bonus(ac, av, env, &i);
	while (i <= ac - 2)
	{
		part_exe_cmd(data, av, i, ac);
		i++;
	}
	close(0);
	my_wait();
	last_free(data);
	return (0);
}
