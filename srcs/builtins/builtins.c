/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/03/29 11:49:30 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_pwd(void)
{
	static char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

void	print_string_array(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = -1;
	while (strings[++i] != NULL)
		ft_printf("%s\n", strings[i]);
}

int	command_env(t_localenv *local)
{
	if (local == NULL)
	{
		printf("Invalid argument: local environment is NULL\n");
		return (-1);
	}
	print_string_array(local->content);
	return (0);
}

int	unset_variable(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index(variable, local->content);
	if (index != -1)
	{
		free(local->content[index]);
		while (local->content[index] != NULL)
		{
			local->content[index] = local->content[index + 1];
			index++;
		}
		local->content[index] = NULL;
		return (0);
	}
	else
		return (-1);
}

int	command_unset(char **cmds, t_localenv *local)
{
	if (cmds == NULL || local == NULL || local->content == NULL)
	{
		printf("Error: Invalid command or local environment.\n");
		return (-1);
	}
	if (cmds[1] == NULL)
	{
		printf("Error: No variable specified for unset.\n");
		return (-1);
	}
	if (unset_variable(cmds[1], local) == 0)
	{
		printf("Variable '%s' unset.\n", cmds[1]);
		return (0);
	}
	else
	{
		printf("Variable '%s' not found.\n", cmds[1]);
		return (-1);
	}
}
