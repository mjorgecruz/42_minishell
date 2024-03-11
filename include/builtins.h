/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:09:13 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/11 10:18:28 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_lstexpand
{
	int					status;
	char				*content;
	struct s_lstexpand	*next;
}				t_lstexpand;

typedef struct s_localenv
{
	char	**content;
}				t_localenv;

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int		command_pwd(void);
void	print_string_array(char **strings);
int		command_env(t_localenv *local);
int		unset_variable(const char *variable, t_localenv *local);
int		command_unset(char **cmds, t_localenv *local);

/* ************************************************************************** */
/*                                   EXPANDER.c                               */
/* ************************************************************************** */

char	*get_ds_code(char *cmd);
char	*ds_replace_codeword(char *cmd, char *code, char *env_val);
char	*expand_single_variable(char *cmd, t_localenv *local);
char	*join_list_contents(t_lstexpand *head);
void	clean_quotes_in_list(t_lstexpand *head, int len);

/* ************************************************************************** */
/*                                 EXPANDER_LST.c                             */
/* ************************************************************************** */

void	insert_lstexpand_node(t_lstexpand **head, t_lstexpand *new_node);
void	free_lstexpand(t_lstexpand *head);
void	create_list_quotes(char *cmd, t_lstexpand **in_cmd_list);
void	expand_content_in_list(t_lstexpand *head, t_localenv *local);

t_lstexpand	*create_node_lstexpand(int status, char *content);

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

char	*master_expander(char *cmd, t_localenv *local);

/* ************************************************************************** */
/*                                  CD_COMMAND.C                              */
/* ************************************************************************** */

int		change_directory(const char *path);
char	*get_home_directory(t_localenv *local);
char	*get_previous_directory(t_localenv *local);
int		update_directories(t_localenv *local, char *cwd);
int		command_cd(char **cmds, t_localenv *local);

/* ************************************************************************** */
/*                                  CD_UTILS.C                                */
/* ************************************************************************** */

void	*ft_realloc(void *ptr, size_t size);
int		add_env_variable(char *name, char *value, t_localenv *local);
int		update_env_variable(char *name, char *value, t_localenv *local);
int		ft_setenv(char *name, char *value, t_localenv *local);

/* ************************************************************************** */
/*                                     ECHO.C                                 */
/* ************************************************************************** */

/* returns true everytime it finds -n or -n 
folowed by n n_times else returns false*/

bool	ft_find_n(char *str);
int		command_echo(char **cmds, t_localenv *local);

/* ************************************************************************** */
/*                                 EXPORT.c                                   */
/* ************************************************************************** */

char	*extract_variable_name(const char *variable);
char	**copy_environment(char **old_env, int num_vars);
int		add_variable(const char *variable, t_localenv *local);
int		update_variable(const char *variable, t_localenv *local);
int		command_export(char **cmds, t_localenv *local);

/* ************************************************************************** */
/*                                EXPORT_UTILS.c                              */
/* ************************************************************************** */

// void		ft_free_str_array(char **ar_str); apagada!!!!
int		find_variable_index_recursive(const char *name, char **env, int index);
int		find_variable_index(const char *variable, char **env);
char	*ft_strncpy(char *dst, const char *src, size_t n);
void	*ft_memalloc(size_t size);

/* ************************************************************************** */
/*                               EXPORT_ENVCPY.c                              */
/* ************************************************************************** */

t_localenv	*env_init(char **envirion);
char	**copy_env_var_utils(char **env, int num_vars, char **env_copy);
char	**copy_environment_variables(char **environ);
void	print_sorted_strings(t_localenv *local);

/* ************************************************************************** */
/*                             EXPORT_UTILS_SORT.c                            */
/* ************************************************************************** */

size_t	ft_strarrlen(char **arr);
char	**ft_strarrdup(char **src);
void	print_next_string(char **str);
void	swap_strings(char **str1, char **str2);

/* ************************************************************************** */
/*                                 FT_GETENV.c                                */
/* ************************************************************************** */

char	*ft_getenv(const char *name, char **envp);

/* ************************************************************************** */
/*                                 EXIT_COMMAND.c                             */
/* ************************************************************************** */

void	command_exit(t_localenv *local);

#endif