/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:32 by masoares          #+#    #+#             */
/*   Updated: 2024/01/27 19:23:47 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains all functions related to memory cleaning*/

#include "minishell.h"

void	clean_cmd_list(t_token *cmd_list, char *paths)
{
	int		i;
	t_token *prev;
	(void) paths;
	
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmds[i].cmds)
		{
			free_split(cmd_list->cmds[i].cmds);
			i++;
		}
		free(cmd_list->cmds);
		free(cmd_list->content);
		prev = cmd_list;
		cmd_list = cmd_list->next;
		free(prev);
		clear_history();
	} 
}


int	free_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (0);
}
