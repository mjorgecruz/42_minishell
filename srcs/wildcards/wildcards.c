/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:50:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/04 13:44:20 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char    *wildcardings(char *str)
{
	char			**new;
    DIR				*dirp;
	struct dirent	*dp;
	char			**wild;
	int				i;

	i = 0;
	new = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	wild = wild_splitter(str);
    dirp = opendir(".");
	if (dirp == NULL)
	{
        perror("Couldn't open '.'");
        return (str);
	}
	closedir(dirp);
	while (wild[i])
	{
		new[i] = NULL;
		ft_printf("%s\n", wild[i]);
		dirp = opendir(".");
		dp = readdir(dirp);
		while (dp != NULL)
		{
        	errno = 0;
            if (dp->d_name[0] != '.' && mega_strncmp(wild[i], dp->d_name) != 0)
                add_wildcard(&new[i], dp->d_name);
			dp = readdir(dirp);
    	}
		ft_printf("%s \n", new[i]);
    	if (errno != 0)
        	perror("Error reading directory");
    	closedir(dirp);
		i++;
	}
	return (wild_rewriter(&str, new));
}

char	*wild_rewriter(char *str, char **wild)
{
	char	*new;
	int		count;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	count = ft_strlen(str);
	while (wild[i])
	{
		count +=  ft_strlen(wild[i]) + 1;
		i++;
	}
	count ++;
	new = ft_calloc(count, sizeof(char));
	while (wild[j])
	{
		
		j++;
	}
	return(NULL);
}

void	add_wildcard(char **wild, char *origin)
{
	char	*trav;
	
	if (*wild == NULL)
	{
		*wild = ft_strcpy(origin);
		return ;
	}
	trav = *wild;
	*wild = ft_strjoin(*wild, " ");
	free(trav);
	trav = *wild;
	*wild = ft_strjoin(*wild, origin);
	free(trav);
}