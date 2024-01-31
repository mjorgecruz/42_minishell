/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/31 11:18:49 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool find_specials_outside_quotes(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i); //ignora inside quotes e espacos
		if	(is_special_char(str[i]))
			return (true);
	}//se encontrar retorna true
	return (false); //nao encontra retorna falso
}