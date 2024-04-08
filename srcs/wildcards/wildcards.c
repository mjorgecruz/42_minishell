/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:50:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/05 17:56:06 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	free_wild_split(char **splitted);

char    *wildcardings(char *str)
{
	char			**new;
    DIR				*dirp;
	struct dirent	*dp;
	char			**wild;
	int				i;
	char			*final;

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
		new[i] = ft_strdup("");
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
		if (new[i] != NULL)
			ft_printf("%s \n", new[i]);
    	if (errno != 0)
        	perror("Error reading directory");
    	closedir(dirp);
		i++;
	}
	new[i] = NULL;
	final = wild_rewriter(str, new, wild);
	free_wild_split(new);
	free_wild_split(wild);
	free(str);
	return (final);
}

char	*wild_rewriter(char *str, char **new, char **wild)
{
	char	*final;
	int		count;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	j = 0;
	count = ft_strlen(str);
	while (new[i])
	{
		count +=  ft_strlen(new[i]) + 1;
		i++;
	}
	count++;
	k = 0;
	i = 0;
	final = ft_calloc(count, sizeof(char));
	while (new[i] || str[j])
	{
		if (wild[i] && mega_wildcmp(wild[i], str, j))
		{
			if (new[i] != NULL)
			{
				k = ft_strlcat(final, new[i], count);
				j += (ft_strlen(wild[i]));
			}	
			i++;
		}
		else
		{
			final[k] = str[j]; 
			k++;
			j++;
		}
	}
	return(final);
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


static int	free_wild_split(char **splitted)
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