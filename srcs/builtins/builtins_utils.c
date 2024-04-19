/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 07:41:15 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 07:41:17 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_string_array(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = -1;
	while (strings[++i] != NULL)
		ft_printf("%s\n", strings[i]);
}

void	prtstr_arr_env(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = -1;
	while (strings[++i] != NULL)
	{
		if (ft_strchr(strings[i], '='))
			ft_printf("%s\n", strings[i]);
	}
}
