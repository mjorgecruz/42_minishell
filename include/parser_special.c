/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/22 15:50:00 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_location(const char *s, int pos)
{
	while (s[pos])
	{
		if (s[pos] == '|')
			return (pos);
		pos++;
	}
	return (-1);
}

bool	check_quotes(const char *str, char q, int pos)  // true if quotes are valid
{
	int	count_before;

	count_before = 0;
	while (pos > -1)
	{
		if (str[pos] == q)
			count_before++;
		pos--;
	}
	if (count_before != 0 && count_before % 2 != 0)
		return (true);
	return (false);
}

bool	count_specials(const char *str, char c, int pos)   //returns true when finding 3 consecutive specials | > <   outside valid quotes
{
	int count;

	while(str[pos])
	{
		count = 0;
		while (c == str[pos])
		{
			count++;
			pos++;
		}
		if (count >= 3)	//finding 3 consecutive
		{
			if	(check_quotes(str, 34, pos) || check_quotes(str, 39, pos)) // if one of these are true then it they are valid i guess
				return(false);
			return (true);
		}
		pos++;
	}
	return (false); //cant find invalid trios thus returning false
}

bool	find_trios(const char *str, int pos)  //upon finding 3 consecutive specials it returns true
{
	int i;
	bool status;

	status = false;
	i = pos;
	while(str[i] && status == false)
	{
		if(str[i] == '>' && status == false)
			status = count_specials(str, '>', i);
		if (str[i] == '<' && status == false)
			status = count_specials(str, '<', i);
		if (str[i] == '|' && status == false)
			status = count_specials(str, '|', i);
		i++;
	}
	return (status);
}

void	parser_special(const char *str)
{
	int i;

	i = iterate_spaces(str, 0);               //passes the whitespaces
	if (i == pipe_location(str, i))              //being a pipe the first non space char = ERROR
	{
		write(1, "DEUMERDA\n", 9);
		return ; //exit aqui e free
	}
	if (find_trios(str, i))                  //if it findes trios of pipes >>> <<< not inside valid aspens returns error (false);
	{
		write(1, "DEUMERDA\n", 9);
		return ; //exit aqui e free
	}
	return ;
}
