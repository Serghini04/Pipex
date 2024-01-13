/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 15:26:09 by meserghi         ###   ########.fr       */
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
	if (!res)
		return (NULL);
	return (res);
}

void	child_run_cmd1(char **av, char **path, int *fd, char **env)
{
	int		read_fd;
	char	**cmd;
	char	*cmd_path;

	read_fd = open(av[1], O_RDWR);
	if (read_fd == -1)
		(free_arr(path), perror("Open error "), exit(1));
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		(free_arr(path), perror("Split error "), exit(0));
	if (dup2(read_fd, 0) == -1 || dup2(fd[1], 1) == -1)
		(free_arr(cmd), free_arr(path), perror("Dup error "), exit(1));
	(close (read_fd), close(fd[1]), close(fd[0]));
	cmd_path = checker_cmd(cmd[0], path);
	if (!cmd_path)
		(free_arr(path), free_arr(cmd), perror("Cmd1 error "), exit(1));
	if (execve(cmd_path, cmd, env) == -1)
	{
		(free_arr(path), free(cmd_path), free_arr(cmd));
		perror("Execve error ");
		exit(1);
	}
}

void	child_run_cmd2(char **av, char **path, int *fd, char **env)
{
	char	*cmd_path;
	char	**cmd;
	int		write_fd;

	write_fd = open(av[4], O_CREAT | O_WRONLY, 0644);
	if (write_fd == -1)
		(free_arr(path), perror("Open error "), exit(1));
	cmd = ft_split(av[3], ' ');
	if (!cmd)
		(free_arr(path), perror("Split error "), exit(1));
	if (dup2(fd[0], 0) == -1 || dup2(write_fd, 1) == -1)
		(free_arr(cmd), free_arr(path), perror("Dup error "), exit(1));
	(close(fd[0]), close(write_fd), close(fd[1]));
	cmd_path = checker_cmd(cmd[0], path);
	if (!cmd_path)
		(free_arr(cmd), free_arr(path), perror("Cmd2 error "), exit(1));
	if (execve(cmd_path, cmd, env) == -1)
	{
		(free_arr(path), free(cmd_path), free_arr(cmd));
		(perror("Execve error "), exit(1));
	}
}

void	parent_exe(char **av, char **path, int *fd, char **env)
{
	int		write_fd;
	int		p;

	p = fork();
	if (p == -1)
		(free_arr(path), perror("fork error "), exit(1));
	if (p == 0)
		child_run_cmd2(av, path, fd, env);
	wait(0);
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	int		fd[2];
	int		p;

	if (ac != 5)
		return (perror("Arg error "), 1);
	path = find_split_path(env);
	if (!path || parsing_arg(av, path) == 0)
		return (free_arr(path), perror("Arg error "), 0);
	if (pipe(fd) == -1)
		return (free_arr(path), perror("Pipe error "), 0);
	p = fork();
	if (p == -1)
		return (free_arr(path), perror("fork error "), 0);
	if (p == 0)
		child_run_cmd1(av, path, fd, env);
	else
	{
		wait(0);
		parent_exe(av, path, fd, env);
	}
}
