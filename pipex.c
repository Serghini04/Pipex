/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 17:47:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (execve(cmd_path, cmd, env) == -1)
	{
		(free_arr(path), free(cmd_path), free_arr(cmd));
		perror("Execve error ");
		exit(1);
	}
	exit(0);
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
	if (execve(cmd_path, cmd, env) == -1)
	{
		(free_arr(path), free(cmd_path), free_arr(cmd));
		(perror("Execve error "), exit(1));
	}
}

void	parent_exe(char **av, char **path, int *fd, char **env)
{
	int		p;

	p = fork();
	if (p == -1)
		(free_arr(path), perror("fork error "), exit(1));
	if (p == 0)
	{
		child_run_cmd2(av, path, fd, env);
	}
}

void f()
{
	system("leaks pipex");
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	int		fd[2];
	int		p;

	atexit(f);
	path = parsing_arg(ac, av, env);
	if (!path)
		return (0);
	if (pipe(fd) == -1)
		return (free_arr(path), perror("Pipe error "), 0);
	p = fork();
	if (p == -1)
		return (free_arr(path), perror("fork error "), 0);
	if (p == 0)
	{
		child_run_cmd1(av, path, fd, env);
	}
	else
	{
		wait(0);
		parent_exe(av, path, fd, env);
	}
}
