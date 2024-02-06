/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:00:04 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/02/06 18:49:53 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */


int	parser_special_first_module(char *str);

bool parser_special_module_two(char *str);

bool	parser_special(char *str);

/* ************************************************************************** */
/*                           PARSER_SPECIAL_UTILS                             */
/* ************************************************************************** */

/*this one checks if the current pipe has any other pipe  after him*/
bool	is_pipe(char* str, int pos);

/* jumps all quotes contents and stops when finding a special char
returns True if there is a special outside quotes or false if didnt find any */
bool find_specials_outside_quotes(char *str);

/* checks string validity in 3 indexs and checks if they are equal returning 0 if not equal and 1 if they are 3 equals */
int	find_same_trio(char *str, int pos);

/*error finding more than 4 special consecutivly with or without spaces in between them*/
int check_invalid_specialcount(char *str, int pos);


/*return 1 if no trios of equals together found and 0  otherwise >>> ||| or <<< or &&&*/
int find_equal_trio_nospaces(char *str);

/* ************************************************************************** */
/*                                 PARSER_PIPE                                */
/* ************************************************************************** */

bool	has_valid_cmd_after(char *str, int pos);
bool    check_combs_doubles(char *str, int pos);
bool    is_invalid_start_sign(char *str);

bool    pipe_is_first(char *s, int *pos);



/* ************************************************************************** */
/*                              SPECIAL_MID_PARSER                            */
/* ************************************************************************** */

int check_pipes(char *str, int pos);
int check_redirs(char *str, int pos);
int check_uppersand(char *str, int pos);
bool mid_parser_iteration(char *str);

#endif