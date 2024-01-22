/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:11:34 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/22 14:41:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <curses.h>
#include <stdbool.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
#include "minishell.h"
	i will receive a string
*/

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}


char *ft_strcpy(char *s)
{
	int i;
	char    *output;
    output = calloc(ft_strlen(s), sizeof(char));
	
	i = 0;
    while (s[i])
	{
        output[i] = s[i];
		i++;
	}
    return(output);
}

void	errors(int error_code)
{
	(void) error_code;
	write(1, "ERRORS\n", 7);
}

//true when it is space
bool	is_space(char c)
{
	if((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

//while finding spaces it will keep going and return the position of the first non space char
// or zero if it wass all spaces or empty

int	iterate_spaces(const char *str, int pos)
{
	while(is_space(str[pos]))
		pos++;
	return(pos);
}

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

void	special_parser(const char *str)
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
	printf("Reached the end of parser all ok;");
	return ;
}

int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
	char *str;
	str = ft_strcpy(argv[1]);
	
	special_parser(str);
	return (0);
}


