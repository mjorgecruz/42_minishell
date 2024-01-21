/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/20 18:02:38 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser_special(char *input)
{
	int     i;
    char    *output;
    
    output = calloc(ft_strlen(input), sizeof(char));
    
    i = 0;
    while (input[i])
    {
        output[i] = input[i];
        i++;
    }
    return(output);
}
