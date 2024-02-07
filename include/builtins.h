#ifndef BUILTINS_H
# define BUILTINS_H

/* ************************************************************************** */
/*                                    BUILTINS                                */
/* ************************************************************************** */

/*
echo (empty) esta a dar seg fault
echo "" esta a imprimir as aspas
echo $expand
"" ou '' tem funcionalidade diferente

*/
int	command_echo(char **cmds_str);
int	command_pwd(void);

// int	command_export();
// int	command_unset();
// int	command_env();
// int	command_exit();

#endif