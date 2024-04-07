/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:02:47 by masoares          #+#    #+#             */
/*   Updated: 2024/04/06 22:22:29 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sig_handler_initial(int sig);
void	sig_handler_kill(int sig);
void	switch_sig_function();
void	switch_sig_readline();
void	switch_sig_default();

#endif
