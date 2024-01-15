/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:53 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/15 13:50:05 by meserghi         ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
	int		fd[2];
	int		read_fd;
	int		write_fd;
}	t_pipex;

int		open_file(t_pipex *data, int ac, char **av);
void	free_struct(t_pipex *data);
void	child_run_cmd1(t_pipex *data, char **env);
void	child_run_cmd2(t_pipex *data, char **env);
int 	if_are_path(char *arg);
char	*ft_strdup(char *s1);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(char *haystack, char *needle, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
t_pipex	*parsing_arg(int ac, char **av, char **env);
char	*checker_cmd(char *str, char **path);
void	free_arr(char **res);

#endif