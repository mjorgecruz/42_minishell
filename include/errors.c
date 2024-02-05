/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:02 by masoares          #+#    #+#             */
/*   Updated: 2024/02/05 11:02:47 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains all error handling functions*/

#include "minishell.h"

void	errors(int error_code, char *cmd)
{
	if (error_code == SYNTAX_NEWLINE)
		printf("minishell:syntax error near unexpected token `newline'");
	else if (error_code == SYNTAX_CLOSE_P)
		printf("minishell:syntax error near unexpected token `)'");
	else if (error_code == SYNTAX_OPEN_P)
		printf("minishell:syntax error near unexpected token `('");
	else if (error_code == SYNTAX_PIPE)
		printf("minishell:syntax error near unexpected token `|'");
	else if (error_code == SYNTAX_D_PIPE)
		printf("minishell:syntax error near unexpected token `||'");
	else if (error_code == SYNTAX_PIPE_AMP)
		printf("minishell:syntax error near unexpected token `||'");
	else if (error_code == SYNTAX_AMP)
		printf("minishell:syntax error near unexpected token `&'");
	else if (error_code == SYNTAX_D_AMP)
		printf("minishell:syntax error near unexpected token `&&'");
	else if (error_code == SYNTAX_AMP_PIPE)
		printf("minishell:syntax error near unexpected token `||'");
	else if (error_code == SYNTAX_CMD)
		printf("minishell:syntax error near unexpected token `%s'", cmd);
}

int	wrong_syntax(char **total_line)
{
	
}