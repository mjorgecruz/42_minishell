/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:08:22 by masoares          #+#    #+#             */
/*   Updated: 2024/04/07 16:15:18 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void		sig_handler_initial(int sig)
{
	(void) sig;
	write(STDIN_FILENO, "\n", 2);
	return ;
}

void		sig_handler_kill(int sig)
{
	(void)	sig;
	
	rl_replace_line("", 0);
	ft_printf("\n");
	rl_done = 1;
	rl_on_new_line();
	return ;
}

void		switch_sig_readline()
{
	signal(SIGINT, sig_handler_kill);
}

void	switch_sig_function()
{
	//signal(SIGINT, SIG_DFL);
	signal(SIGINT, sig_handler_initial);
	signal(SIGQUIT, sig_handler_initial);
}

void	switch_sig_default()
{
	//signal(SIGINT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}