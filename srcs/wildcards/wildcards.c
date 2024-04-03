/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:50:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/03 14:38:43 by masoares         ###   ########.fr       */
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
		// ft_printf("%s\n", wild[i]);
		// i++;
		dirp = opendir(".");
		while (dp != NULL)
		{
        	errno = 0;
			dp = readdir(dirp);
        	if (dp != NULL)
			{
            	if (mega_strncmp(dp->d_name, wild[i]) != 0)
                	add_wildcard(&new[i], dp->d_name);
        	}
    	}
    	if (errno != 0)
        	perror("Error reading directory");
    	closedir(dirp);
	}
	str = wild_rewriter(str, );
	return (NULL);
}

char	*wild_rewriter(char *str,char **wild)
{
	(void) str;
	(void) wild;
	return(NULL);
}
