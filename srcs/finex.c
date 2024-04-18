/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:32 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 12:16:40 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

/*This file contains all functions related to memory cleaning*/

#include "../includes/minishell.h"

void	clean_cmd_list(t_token *cmd_list, char ***heredocs)
{
	if (*heredocs)
		free_split(*heredocs);
	tree_cleaner(cmd_list);
}

int		tree_cleaner(t_token *cmd_list)
{
	int		i;
	
	i = 0;
	if (cmd_list->down)
		tree_cleaner(cmd_list->down);
	if (cmd_list->cmds)
	{
		while (cmd_list->cmds[i].cmds)
		{
			if(cmd_list->cmds[i].cmds[0] != 0)
				free((cmd_list->cmds[i].cmds));
			i++;
		}
	}
	free(cmd_list->cmds);
	free(cmd_list->content);
	if (cmd_list->next)
		tree_cleaner(cmd_list->next);
	free(cmd_list);
	return(1);
}

int	free_split(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted && splitted[i])
		{
			free(splitted[i]);
			i++;
		}
		free(splitted);
		splitted = NULL;
	}
	return (0);
}

// int	finex(t_token **cmd_list, char **paths, char ***heredocs)
// {
		//clear_history();
// } 