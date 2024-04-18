/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:52 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/18 12:14:59 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

t_localenv	*env_init(char **envirion)
{
	t_localenv	*new;

	new = malloc(sizeof(t_localenv));
	if (new == NULL)
	{
		return (NULL);
	}
	new->content = copy_environment_variables(envirion);
	new->sorted = copy_environment_variables(envirion);
	sort_strings(new->sorted, 0, 0, 0);
	return (new);
}

void	copy_env_var_utils(char **env, int num_vars, char **env_copy)
{
	int	len;

	if (*env == NULL)
	{
		env_copy[num_vars] = NULL;
		return;
	}
	len = ft_strlen(*env) + 1;
	env_copy[num_vars] = (char *)malloc(len * sizeof(char));
	if (env_copy[num_vars] == NULL)
	{
		return;
	}
	ft_strncpy(env_copy[num_vars], *env, len);
	copy_env_var_utils(env + 1, num_vars + 1, env_copy);
	return;
}

void	sort_strings(char **strings, int i, int j, int k)
{
	char	*temp;
	char	*var_name1;
	char	*var_name2;

	while (strings[j] != NULL)
		j++;
	while (i < j - 1)
	{
		k = 0;
		while (k < j - i - 1)
		{
			var_name1 = extract_variable_name(strings[k]);
			var_name2 = extract_variable_name(strings[k + 1]);
			if (ft_strncmp(var_name1, var_name2, ft_strlen(var_name1)) > 0)
			{
				temp = strings[k];
				strings[k] = strings[k + 1];
				strings[k + 1] = temp;
			}
			free(var_name1);
			free(var_name2);
			k++;
		}
		i++;
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
	copy_env_var_utils(environ, 0, env_copy);
	return (env_copy);
}

void	put_quotes_expdr(char **arrstr)
{
	int		i;
	int		j;
	bool	equal;

	i = 0;
	while (arrstr[i] != NULL)
	{
		j = 0;
		equal = false;
		ft_putstr_fd("declare -x ", 1);
		while (arrstr[i][j])
		{
			ft_putchar_fd(arrstr[i][j], 1);
			if (arrstr[i][j] == '=' && !equal)
			{
				ft_putchar_fd('"', 1);
				equal = true;
			}
			j++;
		}
		if (ft_strchr(arrstr[i], '='))
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
