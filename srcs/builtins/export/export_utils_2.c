/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:35:28 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 16:39:57 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_variable_name(const char *variable)
{
	int		len;
	char	*name;
	char	*equal_sign;

	len = 0;
	equal_sign = ft_strchr(variable, '=');
	if (equal_sign != NULL)
	{
		while (variable[len] != '=' && variable[len] != '\0')
			len++;
	}
	else
	{
		while (variable[len] != '\0')
			len++;
	}
	name = (char *)ft_memalloc(len + 1);
	if (!name)
		return (NULL);
	len = -1;
	while (variable[++len] != '=' && variable[len] != '\0')
	{
		name[len] = variable[len];
	}
	return (name);
}

int	add_var_cont(const char *variable, t_localenv *local)
{
	int		num_vars;
	char	**new_env;

	if (!local)
		return (EXIT_FAILURE);
	num_vars = 0;
	while (local->content[num_vars] != NULL)
		num_vars++;
	new_env = copy_environment(local->content, num_vars);
	if (!new_env)
		return (EXIT_FAILURE);
	new_env[num_vars] = ft_strdup(variable);
	if (!new_env[num_vars])
	{
		while (num_vars > 0)
			free(new_env[--num_vars]);
		free(new_env);
		return (EXIT_FAILURE);
	}
	num_vars = -1;
	while (local->content[++num_vars])
		free(local->content[num_vars]);
	free(local->content);
	local->content = new_env;
	return (EXIT_SUCCESS);
}

int	update_var_cont(const char *variable, t_localenv *local)
{
	char	*equal_sign;
	char	*variable_copy;
	int		index;

	index = find_variable_index(variable, local->content);
	if (index != -1)
	{
		variable_copy = ft_strdup(variable);
		if (!variable_copy)
			return (EXIT_FAILURE);
		equal_sign = ft_strchr(variable_copy, '=');
		if (!equal_sign)
		{
			free(variable_copy);
			return (EXIT_SUCCESS);
		}
		free(local->content[index]);
		local->content[index] = variable_copy;
		return (EXIT_SUCCESS);
	}
	else
		return (add_var_cont(variable, local));
}

bool	variable_name_check(const char *var)
{
	char	*name;
	bool	ret;

	name = extract_variable_name(var);
	ret = isvar_valid(name);
	free(name);
	return (ret);
}
