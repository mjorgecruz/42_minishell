/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:52 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/10 13:46:02 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

/*
Creates a copy of the environment variables at the start
should be used in a early scope. Returns a structure pointer 
with the env variables in the format of an array of strings 
and a sorted copy of the same to use in export.

Keep in mind aditions and deletions should be 
handled in both arrays for consistency
*/

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
	sort_strings(new->sorted);
	return (new);
}

/*
helper function of the copy_environment_variables
recursive
*/
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

/*
alphabeticaly sorts the array of strings passed to it
used to organize environment varibles order for the export command
 */
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
			if (ft_strcmp(strings[i], strings[j]) > 0)
				swap_strings(&strings[i], &strings[j]);
			j++;
		}
	}
}

/*
Creates and allocates memory for an array of strings
copy of environment variables
*/

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

/*
adds quotation to the strings in the list of the export comand env vars
and adds the prefix "declare -x"
*/

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

/*
Just prints the array of strings no needed but 
*/
int	print_sorted_strings(char **sorted)
{
	put_quotes_expdr(sorted);
	return (EXIT_SUCCESS);
}
