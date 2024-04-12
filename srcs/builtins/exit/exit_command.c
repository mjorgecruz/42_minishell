/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:03:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/12 15:47:52 by luis-ffe         ###   ########.fr       */
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

void free_t_info(t_info info)
{
    int i;

    i = 0;
    while(info.heredocs[i])
    {
        free(info.heredocs[i]);
        i++;
    }
    free(info.heredocs);
}

void    free_info_andlocal_env(t_info info)
{
    int i;

    i = 0;
    while(info.local->content[i])
    {
        free(info.local->content[i]);
        i++;
    }
    i = 0;
    while(info.local->sorted[i])
    {
        free(info.local->sorted[i]);
        i++;
    }
    free(info.local->content);
    free(info.local->sorted);
    free(info.local);
    free_t_info(info);
}

// need to implement binary tree free shit for this 
void free_t_token(t_token tok)
{
    t_token node;
    
    if (tok.content == NULL)
        return;
    if (tok.content != NULL)
        free(tok.content);
    if (tok.cmds->cmds != NULL)
        free(tok.cmds->cmds);
    if (tok.next)
    {
        node = *tok.next;
        free_t_token(node);
    }
    if (tok.down)
    {
        node = *tok.down;
        free_t_token(node);
    }
}

void command_exit(t_info info, char **cmds)
{
    (void) info;
    if (!exit_args_checker(cmds))
        return ;
    free_info_andlocal_env(info);
    free_t_token(*info.token);
    rl_clear_history();
    exit(ex_code(g_signal));
}
