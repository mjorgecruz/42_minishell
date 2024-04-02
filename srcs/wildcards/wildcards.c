/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:50:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/02 16:52:22 by masoares         ###   ########.fr       */
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
                	add_wildcard(new[i], dp->d_name);
        	}
    	}
    	if (errno != 0)
        	perror("Error reading directory");
    	closedir(dirp);
	}
	str = wild_rewriter(str, wild);
	return (NULL);
}

char	**wild_splitter(char *str)
{
	char	**wild;
	int		i;
	int		j;

	i = 0;
	j = 0;
	wild = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	while (str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			if((i == 0 || is_space(str[i - 1])) && (!str[i + 1] || is_space(str[i + 1])))
				wild[j] = add_simple_wildcard(str, &i);
			else if ((i == 0 || is_space(str[i - 1])) && (str[i + 1] && !is_space(str[i + 1])))
				wild[j] = add_forw_wildcard(str, &i);
			else if ((i != 0 && !is_space(str[i - 1])) && is_space(str[i + 1]))
				wild[j] = add_back_wildcard(str, &i);
			else if (!is_space(str[i - 1]) && !is_space(str[i + 1]))
				wild[j] = add_middle_wildcard(str, &i);
			j++;
		}
		i++;
	}
	return (wild);
}

char	*add_simple_wildcard(char *str, int *i)
{
	char	*wildcard;

	(void) str;
	wildcard = (char *) malloc(sizeof(char) * (1 + 1));
	wildcard[0] = '*';
	(*i)++;
	wildcard[*i] = '\0';
	return (wildcard);
}

char	*add_forw_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	beg = *i;
	(*i)++;
	while (str[*i] && !is_space(str[*i]))
		(*i)++;
	end = *i - 1;
	j = 0;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	return (wildcard);
}

char	*add_back_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	end = *i;
	beg = *i;
	while (str[beg] && !is_space(str[beg]))
		(beg)--;
	(beg)++;
	j = 0;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	return (wildcard);
}

char	*add_middle_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	j = 0;
	while (str[*i] && !is_space(str[*i]))
		(*i)++;
	end = *i;
	(*i)--;
	while (*i != 0 && !is_space(str[*i]))
		(*i)--;
	beg = *i + 1;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 1));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	*i = end;
	wildcard[j] = '\0';
	return (wildcard);
}

char	*wild_rewriter(char *str,char **wild)
{
	(void) str;
	(void) wild;
	return(NULL);
}

int		mega_strncmp(char *str, char *comp)
{
	(void) str;
	(void) comp;
	return(0);	
}
