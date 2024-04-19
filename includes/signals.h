/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:02:47 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 14:25:59 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	switch_sig_function(void);
void	switch_sig_new(void);
void	switch_sig_default(void);
void	handle_sigint_status(void);
void	update_status_sigint(int sig);
void	update_status_sigquit(int sig);
void	sig_handler_quit(int sig);
void	sig_handler_int(int sig);

#endif
