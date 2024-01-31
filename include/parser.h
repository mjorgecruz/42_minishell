/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:00:04 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/31 11:20:48 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */

void	parser_special_first_module(const char *str);
void	parser_special(const char *str);

/* ************************************************************************** */
/*                           PARSER_SPECIAL_UTILS                             */
/* ************************************************************************** */

/* jumps all quotes contents and stops when finding a special char
returns True if there is a special outside quotes or false if didnt find any */
bool find_specials_outside_quotes(const char *str);

#endif