/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:35:14 by masoares          #+#    #+#             */
/*   Updated: 2024/01/20 18:02:11 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the first clean-up of the string received in the terminal
It gets rid of the unnecessary quotes*/

#include "minishell.h"

char    *parser_quotes(char *input)
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
