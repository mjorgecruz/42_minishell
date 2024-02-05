/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:00:04 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/02/01 15:46:48 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */


int	parser_special_first_module(const char *str);
void	parser_special(const char *str);

/* ************************************************************************** */
/*                           PARSER_SPECIAL_UTILS                             */
/* ************************************************************************** */

/*this one checks if the current pipe has any other pipe  after him*/
bool	is_pipe(const char* str, int pos);

/* jumps all quotes contents and stops when finding a special char
returns True if there is a special outside quotes or false if didnt find any */
bool find_specials_outside_quotes(const char *str);

/* checks string validity in 3 indexs and checks if they are equal returning 0 if not equal and 1 if they are 3 equals */
int	find_same_trio(const char *str, int pos);

/*error finding more than 4 special consecutivly with or without spaces in between them*/
bool check_invalid_specialcount(const char *str, int pos);


/*return 1 if no trios of equals together found and 0  otherwise >>> ||| or <<< or &&&*/
int find_equal_trio_nospaces(const char *str);

/* ************************************************************************** */
/*                                 PARSER_PIPE                                */
/* ************************************************************************** */

bool	has_valid_cmd_after(const char *str, int pos);
bool    check_combs_doubles(const char *str, int pos);
bool    is_invalid_start_sign(const char *str);

bool    pipe_is_first(const char *s, int pos);

#endif