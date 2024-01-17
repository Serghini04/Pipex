/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:53 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/17 22:50:02 by meserghi         ###   ########.fr       */
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
	int		fd[2];
	int		read_fd;
	int		write_fd;
	int		pos;
	pid_t *pids;
}	t_pipex;

// Utils :
int 	if_are_path(char *arg);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strnstr(char *haystack, char *needle, int len);
void	free_arr(char **res);
void	free_struct(t_pipex *data);
char	**first_part(t_pipex *data, int ac, char **av, char **env);
void	my_close(t_pipex *data);
t_pipex	*parsing_arg(t_pipex *data, int i, char **av, char **path);
char	**find_split_path(char **env);
char	*checker_cmd(char *str, char **path);
int		open_file(t_pipex *data, int ac, char **av);

void	child_run_cmd1(t_pipex *data, char **env);
void	run_cmd2(t_pipex *data, char **env);

void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac);

#endif
