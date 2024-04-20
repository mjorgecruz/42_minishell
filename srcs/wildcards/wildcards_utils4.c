/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:10:32 by masoares          #+#    #+#             */
/*   Updated: 2024/04/20 21:36:11 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wildcard_formatter(char **wildcard, char *str, int *i);

int	wedges(char *str, char *comp)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	if (wback(str, comp) > 0)
		res++;
	while (str[i] != '*')
		i++;
	if(wfront(&str[i], comp) > 0)
		res++;
	if (res < 2)
		return(0);
	else
		return (1);
}

int	wfront(char *str, char *comp)
{
	char	*wildcard;
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 0;
	while (str[i] && str[i] == '*')
		i++;
	wildcard = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (wildcard == NULL)
		return (0);
	while (str[i])
	{
		wildcard[j] = str[i];
		i++;
		j++;
	}
	res = mega_wildcmp(wildcard, comp, ft_strlen(comp) - ft_strlen(wildcard));
	free(wildcard);
	return (res);
}

int	wback(char *str, char *comp)
{
	char	*wildcard;
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '*')
		i++;
	wildcard = ft_calloc(i + 1, sizeof(char));
	if (wildcard == NULL)
		return (0);
	while (str[j] != '*')
	{
		wildcard[j] = str[j];
		j++;
	}
	res = mega_wildcmp(wildcard, comp, 0);
	free(wildcard);
	return (res);
}

int	mega_wildcmp(char *wildcard, char *comp, int start)
{
	int		i;

	i = 0;
	if (start < 0)
		return (0);
	while (wildcard[i] && wildcard[i] == comp[i + start])
		i++;
	if (!wildcard[i])
		return (i + start);
	else
		return (0);
}

int	wmega(char *str, char *comp)
{
	int		res;
	int		i;
	char	*wildcard;

	i = 0;
	res = 0;
	wildcard = NULL;
	while (str[i] == '*')
		i++;
	if (str[0] == '*')
		wildcard = ft_strdup("*");
	else	
		wildcard = ft_strdup("");
	while(str[i])
	{
		wildcard_formatter(&wildcard, str, &i);
		res = order_cmp(wildcard, &comp[res]);
		if (res == 0)
			return (free(wildcard), res);
		free(wildcard);
		wildcard = ft_strdup("*");
	}
	return (free(wildcard), res);
}

static void	wildcard_formatter(char **wildcard, char *str, int *i)
{
	char	*letter;
	char	*prev;

	prev = NULL;
	letter = ft_calloc(2, sizeof(char));
	
	while(str[*i] && str[*i] != '*')
	{
		prev = *wildcard;
		letter[0] = str[*i];
		*wildcard = ft_strjoin(prev, letter);
		free(prev);
		(*i)++;
	}
	if (str[*i] == '*')
	{
		prev = *wildcard;
		letter[0] = str[*i];
		*wildcard = ft_strjoin(prev, letter);
		free(prev);
		(*i)++;
	}
	free(letter);
}
