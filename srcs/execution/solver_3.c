/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:52:04 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 16:53:02 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char	**clean_cmds(t_command *full_cmds, t_localenv *local)
{
	char	*clean;
	char	*clean_2;
	char 	**trav;
	char	**final_cmds;
	int		i;

	clean = clean_str(full_cmds->cmds);
	clean_2 = expander_heredocs(clean, local); 
	trav = ft_split_ignore_quotes(clean_2, " \t\n");
	i = 0;
	while (trav && trav[i] != 0)
		i++; 
	final_cmds = (char **)malloc(sizeof(char *) * (i + 1));
	final_cmds[i] = 0;
	i = 0;
	while (trav[i])
	{
		final_cmds[i] = master_expander_out(trav[i], local);
		i++;
	}
	free(clean_2);
	free_split(trav);
	return (final_cmds);
}

char	*clean_str(char *cmds)
{
	char	*clean;
	int		i;
	int		j;
	char	c;
	
	i = 0;
	j = 0;
	if (!cmds)
		return (NULL);
	clean = ft_calloc(ft_strlen(cmds) + 1, sizeof(char));
	while  (cmds[i])
	{
		if  (cmds[i] == '\"' || cmds[i] == '\'')
		{
			c = cmds[i];
			clean[j] = cmds[i];
			i++;
			j++;
			while (cmds[i] && cmds[i] != c)
			{
				clean[j] = cmds[i];
				i++;
				j++;
			}
		}
		if (cmds[i] == '<' || cmds[i] == '>') 
		{
			while(cmds[i] == '<' || cmds[i] == '>' || cmds[i] == '|')
				i++;
			i = ignore_spaces(cmds, i);
			i = ignore_in_quotes(cmds, i);
			while(cmds[i] && cmds[i] != ' ')
				i++;
			if (!cmds[i])
				break;
		}
		clean[j] = cmds[i];
		i++;
		j++;
	}
	clean[j] = 0;
	return (clean);
}
