/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:36:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/12 23:00:14 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*checker_cmd(char *str, char **path)
{
	int 	i = 0;
	char	*res;

	while (path[i])
	{
		res = ft_strjoin(path[i], str);
		if (!res)
			return (0);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

int	parsing_arg(char **av, char **path)
{
	char **cmd1 = ft_split(av[2], ' ');
	char **cmd2 = ft_split(av[3], ' ');
	if (!cmd1 || !cmd2)
		return 0;
	if (open(av[1], O_RDWR) == -1)
		return (perror("Error "), 0);
	if (!checker_cmd(cmd1[0], path)|| !checker_cmd(cmd2[0], path))
		return (perror("Error cmd "), 0);
	return (1);
}