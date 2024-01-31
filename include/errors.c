/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:02 by masoares          #+#    #+#             */
/*   Updated: 2024/01/31 17:48:50 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains all error handling functions*/

#include "minishell.h"

void	errors(int error_code)
{
	(void) error_code;
	exit(EXIT_FAILURE);
}
