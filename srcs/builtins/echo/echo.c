/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:08:52 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/25 17:22:45 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

bool	ft_find_n(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (false);
	if (str[i] && str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}

// e se o expandido tive -n??
int	command_echo(char **cmds, t_localenv *local)
{
	int		i;
	bool	n_flag;
	char	*exp_temp;

	i = 0;
	n_flag = false;
	while (cmds[++i] && ft_find_n(cmds[i]))
		n_flag = true;
	while (cmds[i] != NULL)
	{
		exp_temp = master_expander(cmds[i], local);
		if (exp_temp)
		{
			printf("%s ", exp_temp);
			free(exp_temp);
		}
		i++;
	}
	if (!n_flag)
		printf("\n");
    return (0);
}
