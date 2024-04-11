/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:03:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/10 14:05:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void command_exit(t_info info)
{
    (void) info;
    rl_clear_history();
    exit(ex_code(g_signal));
    // clean_cmd_list(cmd_list, heredocs);
    // if (local && local->content)
    // {
    //     free_split(local->content);
    //     local->content = NULL;
    // }
	// free(local);
}

/*no fucking clue what commands should be inside to clear all the memory so i nedd your help

on my side only the t_local env has to be cleared

	//necessario dar free disto no scope correto ... nao pode ser na clean comds list que la da erro.
	if (local_env && local_env->content) //corresponde em media se nao forem inseridos comandos a 4820 bytes e esta e a forma correta de lhe dar free
    {
        free_split(local_env->content);
        local_env->content = NULL;
    }
	free(local_env);




errors: 


too many arguments
numeric argument requiered

*/
