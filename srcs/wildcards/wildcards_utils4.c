/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:10:32 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 10:33:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*prev;
	char	*letter;

	i = 0;
	res = 0;
	wildcard = NULL;
	prev = NULL;
	letter = ft_calloc(2, sizeof(char));
	while (str[i] == '*')
		i++;
	if (str[0] == '*')
		wildcard = ft_strdup("*");
	else	
		wildcard = ft_strdup("");
	while(str[i])
	{
		while(str[i] && str[i] != '*')
		{
			prev = wildcard;
			letter[0] = str[i];
			wildcard = ft_strjoin(prev, letter);
			free(prev);
			i++;
		}
		if (str[i] == '*')
		{
			prev = wildcard;
			letter[0] = str[i];
			wildcard = ft_strjoin(prev, letter);
			free(prev);
			i++;
		}
		res = order_cmp(wildcard, &comp[res]);
		if (res == 0)
			return (free(wildcard), free(letter), res);
		free(wildcard);
		wildcard = ft_strdup("*");
	}
	return (free(wildcard), free(letter), res);
}
