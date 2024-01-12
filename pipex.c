/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/13 00:07:26 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	**find_split_path(char **env)
{
	int i = 0;
	int j = 0;
	char *path;
	char **res;
	while (env[i])
	{
		j = 0;
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strnstr(env[i], "PATH=", 5);
			break;
		}
		i++;
	}
	res = ft_split(path, ':');
	if (!res)
		return (NULL);
	return (res);
}

void	child_dir_chi_haraka(char **av, char **path, int *fd, char **env)
{
	int	read_fd;
	char **cmd;

	read_fd = open(av[1], O_RDWR);
	if (read_fd == -1)
		(perror("Error "), exit(1));
	cmd = ft_split(av[2], ' ');
	if (!cmd || dup2(read_fd, 0) == -1 || dup2(fd[1], 1) == -1)
		(perror("Error "), exit(1));
	if (execve(checker_cmd(cmd[0], path), cmd, env) == -1)
		(perror("Error "), exit(1));
}

void	h9(char **av, char **path, int *fd, char **env)
{
	int write_fd;
	char	**cmd;
	int	p;

	write_fd = open(av[4], O_CREAT | O_WRONLY, 0777);
	if (write_fd == -1)
		(perror("Error "), exit(1));
	p = fork();
	if (p == -1)
		(perror("Error "), exit(1));
	cmd = ft_split(av[3], ' ');
	if (p == 0)
	{
		if (!cmd || dup2(fd[0], 0) == -1 || dup2(write_fd, 1) == -1)
			(perror("Error "), exit(1));
		if (execve(checker_cmd(cmd[0], path), cmd, env) == -1)
			(perror("Error "), exit(1));
	}
}

int	main(int ac, char **av, char **env)
{
	char	**path;
	int		fd[2];
	int		p;

	if (ac != 5)
		return (perror(0), 1);
	path = find_split_path(env);
	if (!path || parsing_arg(av, path) == 0)
		return (0);
	if (pipe(fd) == -1)
		return (perror("Error "), 0);
	p = fork();
	if (p == -1)
		return (perror("Error "), 0);
	if (p == 0)
		child_dir_chi_haraka(av, path, fd, env);
	else
		h9(av, path, fd, env);
}
