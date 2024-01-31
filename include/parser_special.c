/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/31 12:27:46 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*como vamos dar os exits disto? e frees?*/

void	parser_special_first_module(const char *str)
{
	if(find_specials_outside_quotes(str) == false) //se nao encontrar specials da avanca direto
	{
		printf("\n\x1b[32m[OK] ->\x1b[0m DIDNT FIND ANY SPECIAL SHOULD JUMP VERIFICATION OF THE NEXT STEPS AND RUN\n");
		return ;
	}
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all in first module should be\n");
	return ;
}

/* i also need to add this to thee header dont touch it i will do it
bool check_invalid_specialcount(const char *str)
{
	int i;
	int count;

	i = -1;
	while (str[++i])
	{
		count = 0;
		while (is_special_char(str[i]))
		{
			if (count > 3)
				return (true);
			count++;
			i++;
		}
		
	}
	return (false);
}

int pipe_is_first(const char *s, int pos)
{
	pos = ignore_spaces(s, pos);
	if (s[pos] == '|')
		return (-1);
	return (0);
}

bool	is_line_after_empty(const char *str, int pos)
{
	while (str[pos] && is_space(str[pos])) //advances spaces
		pos++;
	if	(str[pos] == '\0' || str[pos] == '\n')
		return (true);
	else if (is_special_char(str[pos]))//returns true when finding special even pipes
		return (true);
	return (false);
}

int initial_parser_loop(const char *str)
{
	int i;

	i = 0;
	if (pipe_is_first(str, 0) == -1)//being a pipe the first non space char = ERROR
	{
		printf("\nERROr -> PIPE IN FIRST POSITION\n");
		return (-1);
	}
	while (str[i] && !is_special_char(str[i])) //while no special or inside quotes keep iterating
		i = ignore_in_quotes(str, i);
}

void	parser_special(const char *str)
{
	int i;
	//this will check if there is any amount of consecutive special chars bigger than 3
	if (check_invalid_specialcount(str))
	{
		printf("Invalid Special combination > 3\n");
		return ;
	}
	i = initial_parser_loop(str[0]);
	
	while (str[i]) // correct i
	{
		if (is_special_char(str[i])) //finds special char
			i = //check whatever
		if (is_line_after_empty(str, i) && str[i - 1] != '|')
		{
			printf("\n ERROR EMPTY LINE AFTER SPECIAL CHAR < or >\n");
			return ;
		}
		while (str[i] && !is_special_char(str[i]))
			i = ignore_in_quotes(str, i);		
	}
	printf("\nPASSED SPECIAL PARSER\n");
	return ;
}

*/
