#ifndef BUILTINS_H
# define BUILTINS_H


typedef struct s_lstexpand
{
	int status;
	char *content;
	struct s_lstexpand *next;
} t_lstexpand;

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int	    command_pwd(void);
// int	command_export();
// int	command_unset();
// int	command_env();
// int	command_exit();

/* ************************************************************************** */
/*                                   EXPANDER.c                               */
/* ************************************************************************** */

char	*get_ds_code(char *cmd);
char	*ds_replace_codeword(char *cmd, char *code, char *env_val);
char	*expand_single_variable(char *cmd);
char	*join_list_contents(t_lstexpand *head);
void	clean_quotes_in_list(t_lstexpand *head);

/* ************************************************************************** */
/*                                 EXPANDER_LST.c                             */
/* ************************************************************************** */

t_lstexpand	*create_node_lstexpand(int status, char *content);
void		insert_lstexpand_node(t_lstexpand **head, t_lstexpand *new_node);
void		free_lstexpand(t_lstexpand *head);
void		create_list_quotes(char *cmd, t_lstexpand **in_cmd_list);
void		expand_content_in_list(t_lstexpand *head);

/* ************************************************************************** */
/*                                 EXPANDER_UTILS.c                           */
/* ************************************************************************** */

bool	is_str_empty(char *str);
int		quotes_counter(char *cmd);
char	*ft_strndup(const char *s, size_t n);
int		quotation_size(char *cmd, int start);
void	print_list(t_lstexpand *head);


/* ************************************************************************** */
/*                                 EXPANDER_MAIN.c                            */
/* ************************************************************************** */

char	*master_expander(char *cmd);

/* ************************************************************************** */
/*                                     CD.C                                   */
/* ************************************************************************** */

// int	command_cd();

/* ************************************************************************** */
/*                                     ECHO.C                                 */
/* ************************************************************************** */

/* returns true everytime it finds -n or -n folowed by n n_times else returns false*/
bool	ft_find_n(char *str);
int		command_echo(char **cmds_str);

#endif