/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:04:49 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 00:08:47 by masoares         ###   ########.fr       */
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
void		sig_handler_int(int sig)
{
	(void)	sig;
	
	rl_replace_line("", 0);
	ft_printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
	return ;
}