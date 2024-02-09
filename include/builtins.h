#ifndef BUILTINS_H
# define BUILTINS_H

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

int	command_pwd(void);

// int	command_export();
// int	command_unset();
// int	command_env();
// int	command_exit();

/* ************************************************************************** */
/*                                   EXPANDER.c                               */
/* ************************************************************************** */

// bool is_valid_to_expand(const char *var);
// char    *master_expander(const char *cmd);

/* ************************************************************************** */
/*                                     CD.C                                   */
/* ************************************************************************** */

// int	command_cd();

/* ************************************************************************** */
/*                                     ECHO.C                                 */
/* ************************************************************************** */

int	command_echo(char **cmds_str);

/* returns true everytime it finds -n or -n folowed by n n_times else returns false*/
bool    ft_find_n(char *str);

#endif