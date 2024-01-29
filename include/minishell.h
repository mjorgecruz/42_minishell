/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:50:10 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 10:57:08 by masoares         ###   ########.fr       */
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
# include <linux/limits.h> /*path_max is here size of 4095*/

typedef enum e_builtin
{
	UNDEFINED,
	ECHOS,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
}	t_builtin;

/*Define special characters that separate strings*/
typedef enum e_type
{
	NO_PIPE,
	S_PIPE,
	D_PIPE
}	t_type;

/*Define special characters within the separated strings*/
typedef enum e_special
{
	NONE,
	S_REDIR_IN,
	S_REDIR_OUT,
	D_REDIR_IN,
	D_REDIR_OUT,
	S_AMPER,
	D_AMPER
}	t_special;

typedef struct s_command
{
	char		**cmds;
	t_special	type;
	t_builtin	id;
}	t_command;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_type			next_type;
	t_command		*cmds;
}	t_token;

/*Definition of error cases*/
enum e_ERRORS
{
	ERRO	
};

/* ************************************************************************** */
/*                                TESTERS                                     */
/* ************************************************************************** */

/*in general_executor*/
int tester_function(t_token **list);

/* ************************************************************************** */
/*                               MINISHELL                                    */
/* ************************************************************************** */

/*On start-up, this function clears the terminal before starting execution*/
void	clear_terminal(char *paths);

/* ************************************************************************** */
/*                              HISTORY_MAKER                                 */
/* ************************************************************************** */

/*Get a string from the command line and add to history.
Function sends error signal to ERRORS if anything wrong happens and returns
NULL, and returns the full string otherwise*/
char	*get_line(char *line_read);

/* ************************************************************************** */
/*                             PARSER_GENERAL                                 */
/* ************************************************************************** */

/* General parser function. It must guarantee all clean-up of the string 
received and its freeing. The output is a completely clean string to 
be interpreted*/
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

void	parser_special(const char *str);

/* ************************************************************************** */
/*                               GENERAL_EXECUTOR                             */
/* ************************************************************************** */

/**/
void	general_executer(char *input, char *paths);

/*general function to divide the full line read into parts separated by pipes*/
t_token	*command_organizer(char *input);

/*function used to divide the full line read into parts separated by pipes*/
int		command_divider(t_token **list, t_token *token, char *input);

/*Function to find the next '"' or '''*/ 
int		find_next(char *input, int init_pos);

/* creates new t_token node with the segment of the full line read*/
t_token	*create_node(int init, int end, char *input, t_type type);

/* ************************************************************************** */
/*                              GENERAL_EXECUTOR_2                            */
/* ************************************************************************** */

/*within each element of the linked list created, this function takes care of 
the general division of the partial strings in an array of structs separated by
special characters*/
void	commands_separator(t_token *cmd_list);

/*This function counts the number of special characters that are in the
substring, >> << && etc count as one special character*/
int		specials_counter(t_token *cmd_list);

/*This is an altered version of the split to stop separating at a special
character. We can also make it so it can also complete all the structs instead
of just one*/
char		**mega_split(char *content, int *pos);

char		*write_to_splitted(int count, char *content, int *pos);

int 		ft_count_words(char *content, int pos);

int			find_next_stop(char *content, int pos);

t_special	specials_selector(t_token *cmd_list, int *pos);

int 		count_spaces(int *pos, char *content);

void		fill_cmds(t_token *cmd_list, int specials);

void		pass_quotes(char *content, int *pos);

void		pass_spaces(char *content, int *pos);

/* ************************************************************************** */
/*                              OUT_SETUP_GENERAL                             */
/* ************************************************************************** */

/*discovers what type of command we have as the first argument  and returns 
the enum corresponding to it*/
t_builtin	get_builtin_id(const char *str);

/*gest the previous function working and seting the structure id of the comand
to the correct comand enum id flag*/
void	set_id_flag_cmd(t_token **cmd_list);

/*receives the struct t_comand as argument and will match execution
with it id flag*/
void	exec_correct_builtin(t_command *cmds);

/*defines which function should run the commands sent. It receives the struct
where we can access the arrays of the commands */
void	commands_sorter(t_token **cmd_list);

/*executes commands using the execve function*/
int		command_execve(char *cmd, char *paths);

/* ************************************************************************** */
/*                                    ERRORS                                  */
/* ************************************************************************** */
/*Handle of all errors*/
void	errors(int error_code);

/* ************************************************************************** */
/*                                     FINEX                                  */
/* ************************************************************************** */


void	clean_cmd_list(t_token *cmd_list, char *paths);

/*Handle the memory freeing of an array of strings*/
int		free_split(char **splitted);


/* ************************************************************************** */
/*                                   STR_UTILS                                */
/* ************************************************************************** */

char	*ft_strcpy(char *s);

bool	is_space(char c);

/*while finding spaces it will keep going and return the position of the first
non space char or zero if it wass all spaces or empty*/
int		iterate_spaces(const char *str, int pos);

/*Creates a new node from the line read*/
t_token	*init_struct_cmd(void);

/*adds the node created to the linked list of tokens*/
void	add_token(t_token **tokens, t_token *new);

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int	comand_pwd(void);
// int	command_echo(t_token **cmd_list);
// int	command_cd(t_token **cmd_list);
// int	command_export(t_token **cmd_list);
// int	command_unset(t_token **cmd_list);
// int	command_env(t_token **cmd_list);
// int	command_exit(t_token **cmd_list);

#endif
