/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:01:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 12:00:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_bonus(t_pipex *data)
{
	free_arr(data->cmd);
	free(data->path_cmd);
}

void	last_free(t_pipex *data, char **path)
{
	free_arr(path);
	my_close(data);
	free(data);
}

void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **path)
{
	data->cmd = ft_split(av[i], ' ');
	if (!data->cmd)
		perror("Cmd error ");
	data->path_cmd = checker_cmd(data->cmd[0], path);
	if (!data->path_cmd)
		perror("Cmd error ");
	if (pipe(data->fd) == -1)
		(perror("Pipe error "), last_free(data, path), exit(1));
}

void	part_exe_cmd(t_pipex *data, char **env, int i, int ac)
{
	int	p;

	p = fork();
	if (p == -1)
		(exit(1));
	if (p == 0)
		child_run_cmd1_bonus(data, env, i, ac);
	free_bonus(data);
	if (dup2(data->fd[0], 0) == -1)
		(perror("Dup error "), exit(1));
	(close(data->fd[0]), close(data->fd[1]));
}
void f()
{
	system("lsof -c pipex_bonus");
}

void	here_doc_part(char **av, t_pipex *data)
{
	char	*read;
	data->write_fd = open("my_here_doc", O_RDWR | O_CREAT, 0644);
	if (data->write_fd == -1)
		(free(data), perror("Open error "), exit(1));
	while (1)
	{
		write(1, "here_doc>>", 10);
		read = get_next_line(0);
		if (!ft_strncmp(read, av[2], ft_strlen(av[2])))
			break;
		write(data->write_fd, read, ft_strlen(read));
		free(read);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;
	char	**path;
	int		i;

	i = 2;
	if (ac < 5 || !*env)
		return (perror("Arg error "), 1);
	data = malloc(sizeof(t_pipex));
	if (!data)
		return (1);
	if (!ft_strncmp("here_doc", av[1], 8))
	{
		here_doc_part(av, data);
		i = 3;
	}
	path = first_part(data, ac, av, env);
	while (i <= ac - 2)
	{
		parsing_arg_bonus(data, i, av, path);
		part_exe_cmd(data, env, i, ac);
		i++;
	}
	my_wait();
	last_free(data, path);
	return (0);
}
