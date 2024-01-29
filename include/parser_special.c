/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 16:39:38 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_valid_redirect(const char* str, int pos)      //checks the kind of redirect and if it has a valid comand after
{
	if (str[pos] == '>' || str[pos] == '<')
	{
		if(has_valid_cmd_after(str, pos + 1))
			return (true);
		else if (str[pos] == '>' && is_pipe(str, pos + 1))
			return (true);
	}	
	else if ((str[pos] == '>' || str[pos] == '<') && str[pos] == str[pos + 1])
	{
		if (has_valid_cmd_after(str, pos + 2))
			return (true);
	}
	return (false);
}

bool	is_the_or_sign(const char* str, int pos)  // true if it is a || sign even at the end
{
	if(str[pos] == '|' && str[pos + 1] == '|')
	{
		pos = ignore_spaces(str, pos + 2);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

bool	is_pipe(const char* str, int pos) // true being a valid pipe even at the end
{
	if(str[pos] == '|' && str[pos + 1] != '|')
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

bool	check_signal_validity(const char *str, int pos)
{
	if (is_pipe(str, pos))
	{
		if (has_valid_cmd_after(str, pos)) // after the pipe this needs corrections in the pos and inside the redirect checker afer pipe 
			return (true);
			//checkat os redirects.... depois de pipe
	}
	
	else if (is_the_or_sign(str, pos))
	{
		//CHECKAR PIPE SEGUIDO DE REDIRECT EM FALtA e checkar || comandos que funcionam after or
				
		//ADICIONAR AS FUNTIONS ACIMA POR ORDEM
	}
	else if(is_valid_redirect(str, pos)) //so checkar redirects
		return (true);
	return (false);
		
}

/* Finding more than 3 consecutive specials | < > should give syntax error no matter the position or spaces  they must be outside quotes */
/*OK*/
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
			if (count > 3)
			{
				if (count == 4 && !check_extras(str, pos - count))
				{
					printf("\nINVALID COMB > 3#\n");	
					return (true);
				}
			}
			pos++;
		}
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
}           //returns position at the first non whitespace

int special_parser_mid_to_end_check(const char *str, int pos)
{
	/* needs to check:
	- combination of specials mid and end of string
	- has comand after
	- has no comand after
	- combination can have spaces between specials or not
	
	*/
		
}




void	parser_special(const char *str)
{
	int i;

	i = 0;
	if (pipe_is_first(str, 0) || check_invalid_specialcount(str, 0)) //only >| is valid at start if if has cmd following. this already checks for pipe first and more than
	{
		printf("\nINVALID CHECK\n");
		return ;
	}
	i = find_specials_at_start(str, 0);  // error if start comb invalid or no comand after first specials at the start.
	if (i < 0)
		return ;

	/*
	i is now at the first non whitespace that can be quotes or a special
		should insert here a function that loops throught the string
	
	while (str[i])
	{
		i = special_parser_mid_to_end_check(str, i);
		if (i < 0)
		{
			printf("\n INVALID midtoendparse \n");
			return
		}
	}
	*/
	
	printf("\nPASSED\n");
	return ;
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
