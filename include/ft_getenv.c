/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:28 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/05 00:05:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	size_t	len;
	char	**env_var;

	if (name == NULL || envp == NULL)
		return (NULL);
	len = ft_strlen(name);
	env_var = envp;
	while (*env_var)
	{
		if (ft_strncmp(name, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			return (*env_var + len + 1);
		}
		env_var++;
	}
	return (NULL);
}
