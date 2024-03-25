/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:40:04 by masoares          #+#    #+#             */
/*   Updated: 2024/03/25 00:11:25 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		**pipe_creator(t_token cmds, int **pid)
{
	int		count;
	int		**fd;
	int		i;
	
	count = 0;
	i = 0;
	while (cmds.cmds[count + 1].cmds)
		count++;
	*pid =  (int *) malloc (sizeof(int) * (count + 1));
	fd = (int **) malloc (sizeof(int *) * (count));
	while (i < count)
	{
		fd[i] = (int *) malloc (sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			return (NULL);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

int		close_fd(int ***fd, int pid)
{
	int		j;
	
	j = 0;
	while (j < pid - 1)
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
		j++;
	}
	while ((*fd)[j])
	{
		if (pid == 0 && j == pid)
			close((*fd)[0][0]);
		else if (j == pid - 1)
			close((*fd)[j][1]);
		else if (j == pid)
			close((*fd)[j][0]);
		else if (j > pid)
		{
			close((*fd)[j][0]);
			close((*fd)[j][1]);
		}
		j++;
	}
	return (j);
}
