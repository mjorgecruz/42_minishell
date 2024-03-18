/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:04:07 by masoares          #+#    #+#             */
/*   Updated: 2023/10/26 19:12:58 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		search_temp(char *temp);
void	add_to_temp(char **temp, char **src);
char	*add_to_line(char *temp);
char	*clean_temp(char *temp);
int		ft_strlen(char *str);
char	*ft_calloc(size_t size, int n);
char	*ft_freeing(char **buffer, char **temp);

#endif