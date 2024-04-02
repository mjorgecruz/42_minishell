/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:05:28 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/02 16:56:11 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	size_t	len;
	char	**env_var;

	if (name == NULL || envp == NULL)
		return (NULL);
	len = ft_strlen(name);
	env_var = envp;
	while (*env_var)
	{
		if (ft_strncmp(name, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			return (*env_var + len + 1);
		}
		env_var++;
	}
	return (NULL);
}




//necessita alteracao para so imprimir o que esta depois do igual e nao o nome da propria variavel

int index_locator(char *var, t_localenv *local)
{
    int ret;

	ret = -1;
    ret = find_variable_index_recursive(var, local->content, 0);
    return ret;
}

int	command_printenv(char **cmds, t_localenv *local)
{
	int i;
	int index;

	i = 1;
	if (cmds == NULL || local == NULL || local->content == NULL)
		return (ft_printf("Error: Invalid command or local environment.\n") - 100);
	if (cmds[i] == NULL)
		return (command_env(local));
	if (cmds[i])
	{
		while(cmds[i])
		{
			index = index_locator(cmds[i], local);
			if	(index < 0)
				return (-1);
			else
				ft_printf("%s\n", local->content[index] + ft_strlen(cmds[i]) + 1);
			i++;
		}
	}
	else
		return (ft_printf("Variable '%s' not found.\n", cmds[1]) - 100);
	return (2);
}
