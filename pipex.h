/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:25:53 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/12 22:33:16 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

char	**ft_split(char const *s, char c);
char	*ft_strnstr(char *haystack, char *needle, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		parsing_arg(char **av, char **path);
char	*checker_cmd(char *str, char **path);
#endif