/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:50:10 by masoares          #+#    #+#             */
/*   Updated: 2024/01/22 14:51:51 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <stdbool.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"


// typedef struct s_data
// {
// 	char *input;
// }	t_data;

// t_data	*mini_data_init(void);

// //Tokenizer
// typedef struct s_token
// {
// 	char			*content;
// 	t_type			type;
// }	t_cmdid;

typedef enum e_type
{
	OTHER,
	PIPE,
	CD,
	REDIR_IN,
	REDIR_OUT,
	SIMPLE_QUOTE,
}	t_type;

enum ERRORS
{
	DEU_COCO,
	DEU_CACA,
	PILA_SECA
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
void	ft_parser(char *line_read);

/* ************************************************************************** */
/*                              PARSER_QUOTES                                 */
/* ************************************************************************** */

/*General function to do the first clean-up of the string received in the
terminal. It gets rid of the unnecessary quotes*/
void	parser_quotes(char *input);


/* ************************************************************************** */
/*                             PARSER_SPECIAL                                 */
/* ************************************************************************** */

void	parser_special(char *input);

/* ************************************************************************** */
/*                              OUT_SETUP_GENERAL                             */
/* ************************************************************************** */

int	command_executer(char *cmd, char *paths);

/* ************************************************************************** */
/*                                    ERRORS                                  */
/* ************************************************************************** */

void	errors(int error_code);

/* ************************************************************************** */
/*                                     FINEX                                  */
/* ************************************************************************** */

int	free_split(char **splitted);

/* ************************************************************************** */
/*                                   STR_UTILS                                */
/* ************************************************************************** */

char	*ft_strcpy(char *s);
bool	is_space(char c);

#endif
