/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:08:58 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 14:35:40 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	add_env_variable(char *name, char *value, t_localenv *local)
{
	char	**new_content;
	char	*new_var;
	char	*temp;
	size_t	index;

	index = 0;
	while (local->content[index] != NULL)
		index++;
	new_content = ft_realloc(local->content, (index + 2) * sizeof(char *));
	if (new_content == NULL)
		return (-1);
	local->content = new_content;
	new_var = ft_strjoin(name, "=");
	if (new_var == NULL)
		return (-1);
	temp = new_var;
	new_var = ft_strjoin(new_var, value);
	free(temp);
	if (new_var == NULL)
		return (-1);
	local->content[index] = new_var;
	local->content[index + 1] = NULL;
	return (0);
}

int	update_env_variable(char *name, char *value, t_localenv *local)
{
	size_t	index;
	char	*new_var;
	char	*temp;

	index = 0;
	while (local->content[index] != NULL)
	{
		if (ft_strncmp(local->content[index], name, \
		ft_strlen(name)) == 0 && local->content[index][ft_strlen(name)] == '=')
		{
			free(local->content[index]);
			new_var = ft_strjoin(name, "=");
			if (new_var == NULL)
				return (-1);
			temp = new_var;
			new_var = ft_strjoin(new_var, value);
			free(temp);
			if (new_var == NULL)
				return (-1);
			local->content[index] = new_var;
			return (0);
		}
		index++;
	}
	return (-1);
}

int	add_env_vs(char *name, char *value, t_localenv *local)
{
	char	**new_content;
	char	*new_var;
	char	*temp;
	size_t	index;

	index = 0;
	while (local->sorted[index] != NULL)
		index++;
	new_content = ft_realloc(local->sorted, (index + 2) * sizeof(char *));
	if (new_content == NULL)
		return (-1);
	local->sorted = new_content;
	new_var = ft_strjoin(name, "=");
	if (new_var == NULL)
		return (-1);
	temp = new_var;
	new_var = ft_strjoin(new_var, value);
	free(temp);
	if (new_var == NULL)
		return (-1);
	local->sorted[index] = new_var;
	local->sorted[index + 1] = NULL;
	return (0);
}

int	update_env_vs(char *name, char *value, t_localenv *local)
{
	size_t	index;
	char	*new_var;
	char	*temp;

	index = 0;
	while (local->sorted[index] != NULL)
	{
		if (ft_strncmp(local->sorted[index], name, \
		ft_strlen(name)) == 0 && local->sorted[index][ft_strlen(name)] == '=')
		{
			free(local->sorted[index]);
			new_var = ft_strjoin(name, "=");
			if (new_var == NULL)
				return (-1);
			temp = new_var;
			new_var = ft_strjoin(new_var, value);
			free(temp);
			if (new_var == NULL)
				return (-1);
			local->sorted[index] = new_var;
			return (0);
		}
		index++;
	}
	return (-1);
}

int	ft_setenv(char *name, char *value, t_localenv *local)
{
	if (local == NULL || name == NULL)
		return (-1);
	if (update_env_variable(name, value, local) == -1 || \
		update_env_vs(name, value, local) == -1)
	{
		if (add_env_variable(name, value, local) == -1 || \
			add_env_vs(name, value, local) == -1)
			return (-1);
	}
	return (0);
}
