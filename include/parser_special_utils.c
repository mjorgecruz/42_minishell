/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/02/01 11:54:51 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*returns true if finding any special char outside quote pairs*/
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


//checks string validity in 3 indexs and checks if they are equal returning 0 if not equal and 1 if they are 3 equals.
int	find_same_trio(const char *str, int pos)
{
	if(str[pos] && str[pos + 1] && str[pos + 2])
	{
		if(str[pos] == str[pos + 1] && str[pos + 2] == str[pos])
			return (1);
	}
	return (0);
}