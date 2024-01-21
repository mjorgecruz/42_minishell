/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:50:10 by masoares          #+#    #+#             */
/*   Updated: 2024/01/20 23:18:26 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
# include "./libft/libft.h"


enum ERRORS
{
	DEU_COCO,
	DEU_CACA
	
};

/* ************************************************************************** */
/*                               MINISHELL                                    */
/* ************************************************************************** */

/*On strat-up, this function clears the terminal before starting execution*/
void	clear_terminal(char *paths);

/* ************************************************************************** */
/*                              HISTORY_MAKER                                 */
/* ************************************************************************** */

/*Get a string from the command line and add to history.
Function sends error signal to ERRORS if anything wrong happens and returns NULL, 
and returns the full string otherwise*/
char	*get_line (char *line_read);


/* ************************************************************************** */
/*                             PARSER_GENERAL                                 */
/* ************************************************************************** */

/* General parser function. It must guarantee all clean-up of the string received
and its freeing. The output is a completely clean string to be interpreted*/
char	*ft_parser(char *line_read);

/* ************************************************************************** */
/*                              PARSER_QUOTES                                 */
/* ************************************************************************** */

/*General function to do the first clean-up of the string received in the
terminal. It gets rid of the unnecessary quotes*/
char	*parser_quotes(char *input);


/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */

char	*parser_special(char *input);

/* ************************************************************************** */
/*                              OUT_SETUP_GENERAL                             */
/* ************************************************************************** */

int command_executer(char *cmd, char *paths);

/* ************************************************************************** */
/*                                    ERRORS                                  */
/* ************************************************************************** */

void	errors(int error_code);

/* ************************************************************************** */
/*                                     FINEX                                  */
/* ************************************************************************** */

int free_split(char **splitted);

#endif
