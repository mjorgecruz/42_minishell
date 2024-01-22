/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:13:07 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/22 08:26:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
using in special parser at the moment
*/

bool	is_space(char c)
{
	if((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

char *ft_strcpy(char *s)
{
	int i;
	char    *output;
    output = calloc(ft_strlen(s), sizeof(char));
	
	i = 0;
    while (s[i])
        output[i] = s[i++];
    return(output);
}
