/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:12 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/29 10:32:00 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	find_variable_index_recursive(const char *name, char **env, int index)
{
	if (env[index] == NULL)
		return (-1);
	if (ft_strncmp(name, env[index], ft_strlen(name)) == 0 
		&& env[index][ft_strlen(name)] == '=')
	{
		return (index);
	}
	return (find_variable_index_recursive(name, env, index + 1));
}

int	find_variable_index(const char *variable, char **env)
{
	char	*name;
	int		ret;

	name = extract_variable_name(variable);
	ret = find_variable_index_recursive(name, env, 0);
	free(name);
	return (ret);
}

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*start;

	start = dst;
	while (n > 0 && *src != '\0')
	{
		*dst++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dst++ = '\0';
		n--;
	}
	return (start);
}
