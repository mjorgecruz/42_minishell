/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:59:41 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 14:19:46 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	wild_searcher(char **wild, int *i, char **new);
static char	*wild_transformer(char *wild);
static int	wild_fs_counter(char *str, char **new);

char	*wildcardings(char *str)
{
	char	**new;
	char	**wild;
	int		i;
	char	*final;
	int		res;

	res = 0;
	i = 0;
	new = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	wild = wild_splitter(str, 0, 0, 0);
	while (wild[i] && res == 0)
		res = wild_searcher(wild, &i, new);
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
	return (0);
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
				return (bi_err(wild[i], " : ambiguous redirect", "\n"), \
					free(final), free(decider), "");
			i++;
		}
		final[k++] = str[j++];
	}
	free(decider);
	return (final);
}

int	wild_fs_counter(char *str, char **new)
{
	int	i;
	int	count;

	i = 0;
	count = ft_strlen(str);
	while (new[i])
	{
		count += ft_strlen(new[i]) + 1;
		i++;
	}
	count++;
	return (count);
}
