/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 11:55:48 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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

void print_string_array(char **strings)
{
	int i;
    if (strings == NULL)
        return;
    i = -1;
    while (strings[++i] != NULL)
        printf("%s\n", strings[i]);
}

int command_env(t_localenv *local)
{
    if (local == NULL)
	{
        printf("Invalid argument: local environment is NULL\n");
        return (-1);
    }
	print_string_array(local->content);
    return (0);
}
