/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:59 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 16:26:37 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
returns size of the array
*/

size_t	ft_strarrlen(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/*
makes and returns a copy of the array of strings
*/

char	**ft_strarrdup(char **src)
{
	size_t	len;
	char	**dst;
	size_t	i;

	if (!src)
		return (NULL);
	len = ft_strarrlen(src);
	dst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_split(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	print_next_string(char **str)
{
	while (*str != NULL)
	{
		printf("%s\n", *str);
		str++;
	}
}

/*
used to swap srings in the array during the sort
*/
void	swap_strings(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

int	print_sorted_strings(char **sorted)
{
	put_quotes_expdr(sorted);
	return (EXIT_SUCCESS);
}
