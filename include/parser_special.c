/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/30 12:46:37 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	finds_specials_chars(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_special_char(str[i]))
			return (true);
	}
	return (false);
}

bool check_invalid_specialcount(const char *str, int pos)
{
	int count;

	while (str[pos])
	{
		count = 0;
		pos = ignore_in_quotes(str, pos);
		while (str[pos] && str[pos] != 39 && str[pos] != 34)
		{
			if (is_special_char(str[pos]))
				count++;
			else if (count > 4)
				return (true);
			pos++;
		}
	}
	return (false);
}

bool	valid_start_signals(const char *str)
{
	if (pipe_is_first(str, 0)) //only >| is valid at start if if has cmd following. this already checks for pipe first and more than
	{
		printf("\nINVALID CHECK\n");
		return (false);
	}
	if (find_specials_at_start(str, 0) < 0) // error if start comb invalid or no comand after first specials at the start.
	{
		printf("\nINVALID CHECK\n");
		return (false);
	}
	return (true);
}

void	parser_special(const char *str)
{
	if (finds_specials_chars(str) == false)    			 	//true continua
		return ((void)printf("\nOK\n")); 							//nem corre porque nao encontrou specials
	else if (check_invalid_specialcount(str, 0) == true)	//falso continua
		return ((void)printf("\nKO MANY SPECIALS\n"));			//dar erro direto.
	else if (valid_start_signals(str) == false)				//falso da erro
		return ((void)printf("\nKO MANY SPECIALS\n"));
	//checkar fim.
	//checkar combinacoes do meio.
}

////////////////////////////////////////////////////////////////////

bool	is_the_or_sign(const char* str, int pos)
{
	if(str[pos] == '|' && str[pos + 1] == '|')
	{
		pos = ignore_spaces(str, pos + 2);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

bool	is_pipe(const char* str, int pos)
{
	if(str[pos] == '|' && str[pos + 1] != '|')
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

/*OK*/
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

/*  counts the amount of consecutive specials <>| even with spaces between and returns the count
the above function (has_valid_comand might be redundant due to this one)*/
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
	else if (!check_invalid_specialcount(str, pos))
		return (-1);
	return (pos);
}           //returns position at the first non whitespace