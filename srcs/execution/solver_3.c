/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:52:04 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 12:07:38 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**clean_cmds(t_command *full_cmds, t_localenv *local)
{
	char	*clean;
	char	*clean_2;
	char 	**trav;
	char	**final_cmds;
	int		i;

	clean = clean_str(full_cmds->cmds, 0, 0);
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


static int iterator_clean_str(int i, char *cmds)
{
	i = ignore_spaces(cmds, i);
	i = ignore_in_quotes(cmds, i);
	while(cmds[i] && cmds[i] != ' ')
		i++;
	return (i);
}

static int iterator_clean_str_2(int i, char *cmds)
{
	while(cmds[i] == '<' || cmds[i] == '>' || cmds[i] == '|')
		i++;
	i = iterator_clean_str(i, cmds);
	return (i);
}

char	*clean_str(char *cmds, int i, int j)
{
	char	*clean;
	char	c;
	
	if (!cmds)
		return (NULL);
	clean = ft_calloc(ft_strlen(cmds) + 1, sizeof(char));
	while  (cmds[i])
	{
		if  (cmds[i] == '\"' || cmds[i] == '\'')
		{
			c = cmds[i];
			clean[j++] = cmds[i++];
			while (cmds[i] && cmds[i] != c)
				clean[j++] = cmds[i++];
		}
		if (cmds[i] == '<' || cmds[i] == '>') 
			i = iterator_clean_str_2(i, cmds);
		clean[j++] = cmds[i++];
	}
	clean[j] = 0;
	return (clean);
}
