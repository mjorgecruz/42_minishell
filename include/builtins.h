#ifndef BUILTINS_H
# define BUILTINS_H


typedef struct s_lstexpand
{
	int status;
	char *content;
	struct s_lstexpand *next;
} t_lstexpand;

typedef struct s_localenv
{
	char **content;
} t_localenv;


/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int	    command_pwd(void);
int command_export(char **cmds, char ***local_env_ptr);
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

/* ************************************************************************** */
/*                                 LOCAL_ENV_VAR.c                            */
/* ************************************************************************** */


/*
these will make a copy of the environment variables as a char **envirion   
the env_init will store that pointer in a structur (not needed but fuck it anyway)
and we will pass that structure along to access and edit it.
*/
char **copy_env_var_utils(char **env, int num_vars, char **env_copy);
char **copy_environment_variables(char **environ);
t_localenv *env_init(char **envirion);


#endif