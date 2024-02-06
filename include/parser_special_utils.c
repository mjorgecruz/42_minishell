/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/02/06 16:23:21 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(char* str, int pos)
{
	if (str[pos] == '|' && str[pos + 1] != '|')
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

bool find_specials_outside_quotes(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i);
		if	(is_special_char(str[i]))
			return (true);
	}
	return (false);
}

int	find_same_trio(char *str, int pos)
{
	if (str[pos] && str[pos + 1] && str[pos + 2])
	{
		if(str[pos] == str[pos + 1] && str[pos + 2] == str[pos])
		{
			if (str[pos] == '&')
				errors(SYNTAX_D_AMP, NULL);
			else if (str[pos] == '|')
				errors(SYNTAX_D_PIPE, NULL);
			else if (str[pos + 3] == str[pos] && str[pos + 3] == '<')
				errors(SYNTAX_L_D_REDIR, NULL);
			else if (str[pos + 3] == str[pos] && str[pos + 3] == '>')
				errors(SYNTAX_R_D_REDIR, NULL);			
			else if (str[pos] == '>')
				errors(SYNTAX_R_S_REDIR, NULL);
			else if (str[pos] == '<')
				errors(SYNTAX_L_S_REDIR, NULL);
			return (1);
		}
	}
	return (0);
}

int find_equal_trio_nospaces(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i);
		if (is_special_char(str[i]))
		{
			if (find_same_trio(str, i))
				return (1);
			i++;
		}
	}
	return (0);
}

int check_invalid_specialcount(char *str, int pos)
{
	int count;
	while (str[pos])
	{
		count = 0;
		pos = ignore_in_quotes(str, pos);
		while (str[pos] && str[pos] != 39 && str[pos] != 34)
		{
			if (is_special_char(str[pos]))
			{
				count++;
				pos++;
				if (count > 4)
					return (pos - 4);
			}
			else
			{
				pos = ignore_spaces(str, pos);
				if (!is_special_char(str[pos]))
					count = 0;
				pos++;
			}
		}
	}
	return (-1);
}

/*apagar se necessario era assim que estav antes a funcao anterior mas esta nao parava a encontrar comandos fora de aspas*/
// bool check_invalid_specialcount(const char *str, int pos)
// {
// 	int count;
// 	pos--;
// 	while (str[++pos])
// 	{
// 		count = 0;
// 		pos = ignore_in_quotes(str, pos);
// 		while (str[pos] && str[pos] != 39 && str[pos] != 34)
// 		{
// 			if (is_special_char(str[pos]))
// 			{
// 				count++;
// 				if (count > 4)
// 					return (true);
				
// 			}
// 			pos++;
// 		}
// 	}
// 	return (false);
// }