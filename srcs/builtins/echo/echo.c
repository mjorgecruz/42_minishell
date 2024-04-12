/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:08:52 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/12 11:15:22 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if(str[i - 1] == 'n')
			return (true);
	}
	return (false);
}

int	command_echo(char **cmds, t_localenv *local)
{
	int		i;
	bool	n_flag;
	char	*exp_temp;
	(void)	local;

	i = 0;
	n_flag = false;
	while (cmds[++i] && ft_find_n(cmds[i]))
		n_flag = true;
	while (cmds[i] != NULL)
	{
		exp_temp = ft_strdup(cmds[i]);
		if (exp_temp)
		{
			ft_printf("%s ", exp_temp);
			free(exp_temp);
		}
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
    return (ex_code(EXIT_SUCCESS));
}
