/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:41:20 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 09:43:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_status_sigint(int sig)
{
	if (sig == SIGINT)
		g_signal = 130;
}

void	update_status_sigquit(int sig)
{
	if (sig == SIGQUIT)
		g_signal = 131;
}

void	sig_handler_quit(int sig)
{
	(void) sig;
	write(STDIN_FILENO, "\n", 1);
	g_signal = 131;
	return ;
}

void	sig_handler_int(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
	return ;
}
