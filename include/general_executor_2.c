/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:48:49 by masoares          #+#    #+#             */
/*   Updated: 2024/01/23 15:19:07 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the segmentation of each part of the line read separated by 
pipes. The strings must be divided in parts in an array of structs*/

#include "minishell.h"

void	commands_separator(t_token *cmd_list)
{
	int		specials;
	int		i;

	i = 0;
	while (cmd_list != NULL)
	{
		specials = specials_counter(cmd_list);
		cmd_list->cmds = (t_command *)malloc
			(sizeof(t_command) * (specials + 1));
		while (i < specials + 1)
		{
			cmd_list->cmds[i].cmds = altered_split();
			i++;
		}
		cmd_list = cmd_list->next;
	}
}

int	specials_counter(t_token *cmd_list)
{
}

char	**altered_split()
{
}
