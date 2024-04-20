/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:50:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/20 23:18:45 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	wild_searcher(char **wild, int *i, char **new);
static int	free_wild_split(char **splitted);
static int 	wild_words(char *s);
static int	*check_wild_redirs(char *str, char **wild, char **new);
static char	*wild_transformer(char *wild);
static int	wild_fs_counter(char *str, char **new);
static int	rewriter(char **final, char *wild, char *new, int *j);
static int	decidings(char *str, int k, char *new);

char    *wildcardings(char *str)
{
	char			**new;
	char			**wild;
	int				i;
	char			*final;
	int				res;

	res = 0;
	i = 0;
	new = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	wild = wild_splitter(str, 0, 0, 0);
	while (wild[i] && res == 0)
	{
		res = wild_searcher(wild, &i, new);
	}
	new[i] = NULL;
	final = wild_rewriter(str, new, wild, 0);
	free_wild_split(new);
	free_wild_split(wild);
	free(str);
	return (final);
}
static int	wild_searcher(char **wild, int *i, char **new)
{
	char			*trav;
	DIR				*dirp;
	struct dirent	*dp;
	
	trav = wild_transformer(wild[*i]);
	new[*i] = ft_strdup("");
	dirp = opendir(".");
	dp = readdir(dirp);
	while (dp != NULL)
	{
       	errno = 0;
        if (dp->d_name[0] != '.' && mega_strncmp(trav, dp->d_name) != 0)
            add_wildcard(&new[*i], dp->d_name);
		dp = readdir(dirp);
    }
    if (errno != 0)
	{
       	perror("Error reading directory");
		return (-1);
	}
	closedir(dirp);
	(*i)++;
	free(trav);
	return(0);
}

static char	*wild_transformer(char *wild)
{
	int		i;
	int		j;
	char	asps;
	char	*trav;
	
	i = 0;
	j = 0;
	trav = ft_calloc(ft_strlen(wild) + 1, sizeof(char));
	while (wild[i])
	{
		if (wild[i] == '\"' || wild[i] == '\'')
		{
			asps = wild[i];
			i++;
			while (wild[i] != asps)
				trav[j++] = wild[i++];
			i++;
		}
		if (wild[i])
			trav[j++] = wild[i++];
	}
	return (trav);
}

char	*wild_rewriter(char *str, char **new, char **wild, int k)
{
	char	*final;
	int		i;
	int		j;
	int		*decider;
	
	i = 0;
	j = 0;
	k = 0;
	decider = check_wild_redirs(str, wild, new);
	final = ft_calloc(wild_fs_counter(str, new), sizeof(char));
	while (new[i] || str[j])
	{
		if (wild[i] && mega_wildcmp(wild[i], str, j))
		{
			if (decider[i] == 0)
				k = rewriter(&final, wild[i], new[i], &j);
			else if (decider[i] < 0)
				return(ft_printf("ambiguous redirect"),
					free(final), free(decider), "");
			i++;
		}
		final[k++] = str[j++]; 
	}
	free(decider);
	return(final);
}

int		wild_fs_counter(char *str, char **new)
{
	int i;
	int count;
	
	i = 0;
	count = ft_strlen(str);
	while (new[i])
	{
		count +=  ft_strlen(new[i]) + 1;
		i++;
	}
	count++;
	return(count);
}

int		rewriter(char **final, char *wild, char *new, int *j)
{
	int k;
	
	if (new[0] == 0)
	{
		k = ft_strlcat(*final, wild, ft_strlen(*final) + ft_strlen(wild) + 2);
		(*j) += (ft_strlen(wild));
	}
	else if (new != NULL)
	{
		k = ft_strlcat(*final, new, ft_strlen(*final) + ft_strlen(new) + 2);
		(*j) += (ft_strlen(wild));
	}
	return (k);
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

static int	*check_wild_redirs(char *str, char **wild, char **new)
{
	int		i;
	int		j;
	int		k;
	int 	*decider;
	
	i = 0;
	j = 0;
	k = 0;
	while (new[i])
		i++;
	decider = (int *)malloc(sizeof(int) * i);
	i = 0; 
	while (new[i] || str[j])
	{
		if (wild[i] && mega_wildcmp(wild[i], str, j))
		{
			k = j;
			k--;
			decider[i] = decidings(str, k, new[i]);
			i++;
		}
		j++;
	}
	return(decider);
}

int	decidings(char *str, int k, char *new)
{
	int		decider;

	decider = 0;
	while (k >= 0 && is_space(str[k]))
		k--;
	if (k == -1 || (str[k] != '<' && str[k] != '>'))
		decider = 0;
	else if (str[k] == '<' && str[k - 1] == '<')
		decider = 1;
	else if (str[k] == '<')
	{
		if (wild_words(new) > 1)
			decider = -1;
	}
	else if (str[k] == '>')
	{
		if (wild_words(new) > 1)
			decider = -2;
	}
	return (decider);	
}

static int 	wild_words(char *s)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (is_space(s[i])) 
			i++;
		if (s[i] != '\0')
			count++;
		while (!is_space(s[i]) && s[i] != '\0')
		{	
			i++;
		}
	}
	return (count);
}
