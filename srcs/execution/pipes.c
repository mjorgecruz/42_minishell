/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:40:04 by masoares          #+#    #+#             */
/*   Updated: 2024/03/25 10:24:28 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	(void) pid;
	j = 0;
	while ((*fd)[j])
	{
		close((*fd)[j][0]);
		close((*fd)[j][1]);
		j++;
	}
	return (j);
}

int		**fd_creator(t_token cmds, int **pid)
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
	fd[i] = NULL;
	return (fd);
}

int		*pipe_creator_2()
{
	int		*fd;
	
	fd = (int *) malloc (sizeof(int) * 2);
	if (pipe(fd) == -1)
		return (NULL);
	return (fd);
}