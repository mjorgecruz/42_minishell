/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/10 10:25:56 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_var_cont(const char *variable, t_localenv *local);
int	add_var_cont(const char *variable, t_localenv *local);

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


// export: `$': not a valid identifier  todos os simbolos que nao forem os aceites tem de dar codigo 1 e imprimir
//export: `$': not a valid identifier

/*
TO DO:

EXPORT:
	Reduzir para 25 linhas
	erros em todas as mensagens para STDERR_FILENO
	criar function
	dont allow invalid chars
	
SIGNALS: to do;

CD: check working with ~ and others

PWD: check 

ECHO: verificar $? $_

EXIT: todo;
*/

bool isvar_valid(const char *name)
{
    if (name == NULL || ft_isdigit(*name))
        return false;
    while (*name)
    {
        if (!ft_isalnum(*name) && *name != '_')
            return false;
        name++;
    }
    return true;
}

bool variable_name_check(const char *var)
{
	char *name;
	bool ret;
	
	name = extract_variable_name(var);
	ret = isvar_valid(name);
	free(name);
	return (ret);
}

int command_export(char **cmds, t_localenv *local)
{
	char *variable;
	char *equal_sign;
    int i;

	i = 0;
    if (cmds[1] == NULL)
        return (ex_code(print_sorted_strings(local->sorted)));
    while (cmds[++i] != NULL)
    {
        variable = cmds[i];
        equal_sign = ft_strchr(variable, '=');  // aqui
        if (equal_sign == variable || !variable_name_check(variable)) // adicionar function that checks if it is a valid variable
        {
			builtin_errors("export: `", variable, "': not a valid identifier\n");
            return (ex_code(EXIT_FAILURE));
        }
        if (find_variable_index(variable, local->sorted) == -1)
		{	
			if (add_variable(variable, local) || add_var_cont(variable, local))
				return(ex_code(EXIT_FAILURE));
		}
        if (update_variable(variable, local) || update_var_cont(variable, local))
            return (ex_code(EXIT_FAILURE));
    }
    return (EXIT_SUCCESS);
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
