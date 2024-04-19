/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:41:46 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 09:42:13 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	switch_sig_function(void)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, SIG_IGN);
}

void	switch_sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	switch_sig_new(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_status(void)
{
	signal(SIGINT, update_status_sigint);
	signal(SIGQUIT, update_status_sigquit);
}
