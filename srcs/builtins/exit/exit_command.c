/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:03:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/12 10:09:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool is_arg_valid_numeric(const char *str)
{
    int i;
    
    i = 0;
    while (is_space(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!ft_isdigit(str[i]))
        return (false);
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            i++;
        else
            return (false);
    }
    if (str[i] == '\0')
        return (true);
    return (false);
}


static bool exit_args_checker(char **cmds)
{
    if (!cmds[1])
        return (ex_code(0), true);
    if (cmds[2])
    {
        builtin_errors("exit: too many arguments", "\n", "");
        return (ex_code(1), false);
    }
    if (cmds[1] && !cmds[2])
    {
        if (is_arg_valid_numeric(cmds[1]))
            return(ex_code(ft_atoi(cmds[1])), true);
        else
        {
            builtin_errors("exit: invalid numeric argument", "\n", "");
            return(ex_code(1), false);   
        }
    }
    else
        return(ex_code(1), false);
}

//necessari oadicionar todas as estruturas que temos de dar free
void command_exit(t_info info, char **cmds)
{
    (void) info;

    if (!exit_args_checker(cmds))
        return ;
    rl_clear_history();
    exit(ex_code(g_signal));
}
