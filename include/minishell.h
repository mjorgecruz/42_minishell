/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:50:10 by masoares          #+#    #+#             */
/*   Updated: 2024/01/19 12:41:55 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
# include "./libft/libft.h"

/* ************************************************************************** */
/*                               MINISHELL                                    */
/* ************************************************************************** */
 
char	*rl_gets (char *line_read);

int free_split(char **splitted);

/* ************************************************************************** */
/*                              HISTORY_MAKER                                 */
/* ************************************************************************** */
/*Get a string from the command line and add to history.
Function sends error signal to ERRORS if anything wrong happens, 
and returns the full string otherwise*/
char	*rl_gets (char *line_read);


/* ************************************************************************** */
/*                              PARSER_QUOTES                                 */
/* ************************************************************************** */
void  parser_quotes(char *line_read);

#endif
