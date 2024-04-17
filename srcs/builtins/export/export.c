/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 16:39:51 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		return (EXIT_FAILURE);
	num_vars = 0;
	while (local->sorted[num_vars] != NULL)
		num_vars++;
	new_env = copy_environment(local->sorted, num_vars);
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
	while (local->sorted[++num_vars])
		free(local->sorted[num_vars]);
	free(local->sorted);
	local->sorted = new_env;
	return (EXIT_SUCCESS);
}

int	update_variable(const char *variable, t_localenv *local)
{
	char	*equal_sign;
	char	*variable_copy;
	int		index;

	if (!local || !local->sorted)
		return (EXIT_FAILURE);
	index = find_variable_index(variable, local->sorted);
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
		free(local->sorted[index]);
		local->sorted[index] = variable_copy;
		return (EXIT_SUCCESS);
	}
	else
		return (add_variable(variable, local));
}

bool	isvar_valid(const char *name)
{
	if (name == NULL || ft_isdigit(*name))
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

int	command_export(char **cmds, t_localenv *local)
{
	char	*var;
	char	*equal_sign;
	int		i;

	i = 0;
	if (cmds[1] == NULL)
		return (ex_code(print_sorted_strings(local->sorted)));
	while (cmds[++i] != NULL)
	{
		var = cmds[i];
		equal_sign = ft_strchr(var, '=');
		if (equal_sign == var || !variable_name_check(var))
		{
			bi_err("export: `", var, "': not a valid identifier\n");
			return (ex_code(EXIT_FAILURE));
		}
		if (find_variable_index(var, local->sorted) == -1)
		{
			if (add_variable(var, local) || add_var_cont(var, local))
				return (ex_code(EXIT_FAILURE));
		}
		if (update_variable(var, local) || update_var_cont(var, local))
			return (ex_code(EXIT_FAILURE));
	}
	return (ex_code(EXIT_SUCCESS));
}
