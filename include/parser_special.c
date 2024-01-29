/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 10:53:58 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finding more than 3 cpnsecutive specials | < > should give syntax error no matter the position */

bool check_invalid_specialcount(const char *str) // not checking quotes.
{
	int i;
	int count;

	i = -1;
	i = ignore_in_quotes(str, i);
	while (str[++i])
	{
		count = 0;
		i = ignore_in_quotes(str, i);
		while (is_special_char(str[i]))
		{
			if (count > 3)
			{
				printf("\nINVALID COMB > 3#\n");
				return (true);
			}
			count++;
			i++;
		}
	}
	return (false);
}


bool pipe_is_first(const char *s, int pos)
{
	pos = ignore_spaces(s, pos);
	if (s[pos] == '|')
	{
		printf("\nINVALID PIPE\n");
		return (true);
	}
	return (false);
}

/* receives the position in the string and will check for a valid comand until it finds the next special  
return: false finding a special char and nothing else in the path it started until that special*/
bool	has_valid_cmd_after(const char *str, int pos)
{
	pos = ignore_spaces(str, pos);
	if (is_special_char(str[pos]))
		return (false);
	else
		return (true);
}

/*  counts the amount of consecutive specials <>| even with spaces between and returns the count
the above function (has_valid_comand might be redundant due to this one)

return: the count of special chars even with whitespaces in between */
int count_consecutive_specials(const char *str, int pos)
{
	int count;

	count = 0;
	pos = ignore_spaces(str, pos);
	while (is_special_char(str[pos]) && str[pos])
	{	count++;
		pos++;
		pos = ignore_spaces(str, pos);
	}
	return (count);
}


bool is_allowed_start_comb(const char *str, int pos)
{
	if (str[pos] == '>' && str[pos + 1] == '|' && str[pos + 2])
	{
		if (has_valid_cmd_after(str, pos + 2)) //if no comand after or if just empty it will not return true
			return (true);
	}
	else if ((str[pos] == '>' || str[pos] == '<') && str[pos + 1])
	{
		if (has_valid_cmd_after(str, pos + 1))
			return (true);
	}
	return (false);  //false means shouldnt run because has no comand after or invalid combination or spaces between specials.
}



/*returns position at the first non whitespace if there was any invalid starting vomb it should give error
return on error = NOT VALID
*/
int	find_specials_at_start(const char *str, int pos)
{
	int count;

	count = 0;
	pos = ignore_spaces(str, pos);
	count = count_consecutive_specials(str, pos); //ignores spaces and counts specials (stops when finding something that isnt special nor whitespace)
	if (count > 2)
	{
		printf("\nNOT VALID\n");
		return (-1);
	}
	else if (count != 0)
	{
		if (!is_allowed_start_comb(str, pos))
		{
			printf("\nNOT VALID\n");
			return (-1);
		}
	}
	return (pos);
}//returns position at the first non whitespace






void	parser_special(const char *str)
{
	int i;

	i = 0;
	if (pipe_is_first(str, 0) || check_invalid_specialcount(str))  //error if special count error or if pipe in first
	{
		printf("\nINVALID CHECK\n");
		return ;
	}
	i = find_specials_at_start(str, 0);  // error if start comb invalid or no comand after first specials at the start.
	if (i < 0)
		return ;
	// i is now in the position of the first non whitespace beeing it a special or any other char.
	printf("\nPASSED\n");
	return ;
}

/*
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
