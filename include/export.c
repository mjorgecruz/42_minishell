/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/11 13:31:44 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**copy_environment(char **old_env, int num_vars)
{
	char	**new_env;
	int		i;

	new_env = (char **)ft_memalloc((num_vars + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < num_vars)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[num_vars + 1] = NULL;
	return (new_env);
}

int	add_variable(const char *variable, t_localenv *local)
{
	int		num_vars;
	char	**new_env;

	if (!local)
		return (-1);
	num_vars = 0;
	while (local->content[num_vars] != NULL)
		num_vars++;
	new_env = copy_environment(local->content, num_vars);
	if (!new_env)
		return (-1);
	new_env[num_vars] = ft_strdup(variable);
	if (!new_env[num_vars])
	{
		while (num_vars > 0)
			free(new_env[--num_vars]);
		free(new_env);
		return (-1);
	}
	num_vars = -1;
	while (local->content[++num_vars])
		free(local->content[num_vars]);
	local->content = new_env;
	return (0);
}

int	update_variable(const char *variable, t_localenv *local)
{
	char	*equal_sign;
	char	*variable_copy;
	int		index;

	if (!local || !local->content)
		return (-1);
	index = find_variable_index(variable, local->content);
	if (index != -1)
	{
		variable_copy = ft_strdup(variable);
		if (!variable_copy)
			return (-1);
		equal_sign = ft_strchr(variable_copy, '=');
		if (!equal_sign)
		{
			free(variable_copy);
			return (-1);
		}
		free(local->content[index]);
		local->content[index] = variable_copy;
		return (0);
	}
	else
		return (add_variable(variable, local));
}

int	command_export(char **cmds, t_localenv *local)
{
	char	*variable;
	char	*equal_sign;

	if (cmds == NULL || local == NULL || local->content == NULL)
		return (-1);
	if (cmds[1] == NULL)
	{
		print_sorted_strings(local);
		return (-2);
	}
	variable = cmds[1];
	equal_sign = ft_strchr(variable, '=');
	if (equal_sign == NULL || equal_sign == variable)
		return (-1);
	if (update_variable(variable, local) == 0)
		return (0);
	else
		return (-1);
}

// void error_if_export_invalid_format(char **cmds)
// {
//     char *variable;
	
// 	variable = cmds[1];
//     for (int i = 0; variable[i] != '\0'; i++) {
//         char c = variable[i];
//         if (!(c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
//             printf("Invalid variable name: Only alphanumeric characters and '_' allowed.\n");
//             return;
//         }
//     }
//     printf("Export command format is valid.\n");
// }
