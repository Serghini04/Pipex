/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:53 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/18 13:54:45 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmd;
	char	*path_cmd;
	int		*pids;
	int		fd[2];
	int		read_fd;
	int		write_fd;
	int		pos;
}	t_pipex;

// Mandatory part ...
void	child_run_cmd1(t_pipex *data, char **env);
void	run_cmd2(t_pipex *data, char **env);
char	**find_split_path(char **env);
char	*checker_cmd(char *str, char **path);
int		open_file(t_pipex *data, int ac, char **av);
void	parsing_arg(t_pipex *data, int i, char **av, char **path);
char	**first_part(t_pipex *data, int ac, char **av, char **env);

// Utils ...
int		if_are_path(char *arg);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strnstr(char *haystack, char *needle, int len);
void	free_arr(char **res);
void	my_close(t_pipex *data);
void	my_wait(t_pipex *data);
void	free_struct(t_pipex *data);

// Bonus part ...
void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **path);
void	part_exe_cmd(t_pipex *data, char **env, int i, int ac);
void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac);

#endif
