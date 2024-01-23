/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:58:50 by meserghi          #+#    #+#             */
/*   Updated: 2024/01/23 10:13:14 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_check(char *str);
char	*get_next_line(int fd);
char	*next_line(char *str);
char	*clean_res(char *str);
char	*ft_get_read(int fd, char *res);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_fill(char *s1, char *s2, char *res);
int		ft_str_len(char *s);
char	*ft_str_join(char *s1, char *s2);

#endif
