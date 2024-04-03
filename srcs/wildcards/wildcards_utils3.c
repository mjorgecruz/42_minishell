/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:56:57 by masoares          #+#    #+#             */
/*   Updated: 2024/04/03 14:38:00 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	wild_definer(char *wildcard);
static int	ignore_ast(char *str, int i);
static int  wild_definer_a(char *wildcard);
static int  wild_definer_b(char *wildcard);

int		mega_strncmp(char *str, char *comp)
{
	(void) comp;
	int		wild_type;

	wild_type = wild_definer(str);
	if (wild_type == WILD_ONE)
		return (1);
	else if (wild_type == WILD_FRONT)
        return(wfront(str, comp));
	else if (wild_type == WILD_BACK)
        return(wback(str, comp));
    else if (wild_type == WILD_MIDDLE)
		return(wmiddle(str, comp));
    else if (wild_type == WILD_EDGES)
        return(wedges(str, comp));
    else if (wild_type == WILD_MEGA_BACK)
        return(wmega_back(str, comp));
    else if (wild_type == WILD_MEGA_BACK)
        return(wmega(str, comp));
	return(0);	
}

static int  wild_definer(char *wildcard)
{
	if (wildcard[0] == '*')
        return(wild_definer_a(wildcard));
	else
        return(wild_definer_b(wildcard));
}

static int	ignore_ast(char *str, int pos)
{
	while (str[pos] && str[pos] == '*')
		pos++;
	return(pos);
}

static int  wild_definer_a(char *wildcard)
{
    int     i;
    
    i = 0;
    i = ignore_ast(wildcard, i);
	if (!wildcard[i])
    	return (WILD_ONE);
	while (wildcard[i] && wildcard[i] != '*')
		i++;
	if (!wildcard[i])
		return (WILD_FRONT);
	i = ignore_ast(wildcard, i);
	if (!wildcard[i])
		return (WILD_MIDDLE);
	return (MEGA_WILD);
}

static int  wild_definer_b(char *wildcard)
{
    int     i;

    i = 0;
    while (wildcard[i] && wildcard[i] != '*')
		i++;
	i = ignore_ast(wildcard, i);
	if (!wildcard[i])
		return (WILD_BACK);
	while (wildcard[i] && wildcard[i] != '*')
		i++;
	if (!wildcard[i])
		return (WILD_EDGES);
	return (WILD_MEGA_BACK);
}
