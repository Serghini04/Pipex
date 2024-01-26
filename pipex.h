/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:53 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/26 18:12:27 by meserghi         ###   ########.fr       */
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
	char	**env;
	int		fd[2];
	int		read_fd;
	int		write_fd;
}	t_pipex;


// Mandatory part ...
void	child_run_cmd1(t_pipex *data, char **env);
void	run_cmd2(t_pipex *data, char **env);
char	**find_split_path(char **env);
char	*checker_cmd(char *str, char **path);
void	parsing_arg(t_pipex *data, int i, char **av, char **env);
t_pipex	*first_part(int ac, char **env, int *p);

// Utils ...
int		if_are_path(char *arg);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, int b);
int		ft_strlen(char *s);
char	*ft_strnstr(char *haystack, char *needle, int len);
void	free_arr(char **res);
void	my_close(t_pipex *data, int i);
void	my_wait(void);
void	free_struct(t_pipex *data, int i);
int		ft_strcmp(char *s1, char *s2);

// Bonus part ...
void	parsing_arg_bonus(t_pipex *data, int i, char **av, char **env);
void	part_exe_cmd(t_pipex *data, char **av, int i, int ac);
void	open_file(t_pipex *data, int ac, char **av, char *check);
void	child_run_cmd1_bonus(t_pipex *data, char **env, int i, int ac);
void	last_free(t_pipex *data);
char	*get_next_line(int fd);
void	here_doc_part(char **av, t_pipex *data);

#endif
