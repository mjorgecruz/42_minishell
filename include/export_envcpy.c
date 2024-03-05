/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:52 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/05 00:04:55 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_localenv	*env_init(char **envirion)
{
	t_localenv	*new;

	new = malloc(sizeof(t_localenv));
	if (new == NULL)
	{
		return (NULL);
	}
	new->content = copy_environment_variables(envirion);
	return (new);
}

char	**copy_env_var_utils(char **env, int num_vars, char **env_copy)
{
	int	len;

	if (*env == NULL)
	{
		env_copy[num_vars] = NULL;
		return (env_copy);
	}
	len = ft_strlen(*env) + 1;
	env_copy[num_vars] = (char *)malloc(len * sizeof(char));
	if (env_copy[num_vars] == NULL)
	{
		return (NULL);
	}
	ft_strncpy(env_copy[num_vars], *env, len);
	return (copy_env_var_utils(env + 1, num_vars + 1, env_copy));
}

void	sort_strings(char **strings)
{
	int	i;
	int	j;

	i = -1;
	while (strings[++i] != NULL)
	{
		j = i + 1;
		while (strings[j] != NULL)
		{
			if (strcmp(strings[i], strings[j]) > 0)
				swap_strings(&strings[i], &strings[j]);
			j++;
		}
	}
}

char	**copy_environment_variables(char **environ)
{
	int		num_vars;
	char	**env;
	char	**env_copy;

	num_vars = 0;
	env = environ;
	while (*env != NULL)
	{
		num_vars++;
		env++;
	}
	env_copy = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (env_copy == NULL)
		return (NULL);
	return (copy_env_var_utils(environ, 0, env_copy));
}

void	print_sorted_strings(t_localenv *local)
{
	char	**temp_content;
	char	**temp_content_start;
	int		i;

	if (local == NULL || local->content == NULL)
		return ;
	temp_content = ft_strarrdup(local->content);
	if (temp_content == NULL)
		return ;
	temp_content_start = temp_content;
	sort_strings(temp_content);
	i = -1;
	while (temp_content[++i] != NULL)
		printf("declare -x %s\n", temp_content[i]);
	while (*temp_content)
	{
		free(*temp_content);
		temp_content++;
	}
	free(temp_content_start);
}
