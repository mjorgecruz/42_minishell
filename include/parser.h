/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:00:04 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/02/01 11:56:11 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */

/*return 1 if no trios of equals together found and 0  otherwise >>> ||| or <<< or &&&*/
int find_equal_trio_nospaces(const char *str);

int	parser_special_first_module(const char *str);
void	parser_special(const char *str);

/* ************************************************************************** */
/*                           PARSER_SPECIAL_UTILS                             */
/* ************************************************************************** */

/* jumps all quotes contents and stops when finding a special char
returns True if there is a special outside quotes or false if didnt find any */
bool find_specials_outside_quotes(const char *str);

//checks string validity in 3 indexs and checks if they are equal returning 0 if not equal and 1 if they are 3 equals.
int	find_same_trio(const char *str, int pos);
#endif