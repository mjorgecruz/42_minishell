/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:02 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 11:56:21 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

/*This file contains all error handling functions*/

#include "../../includes/minishell.h"

void	code_2(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ex_code(2);
}

void	errors(int error_code, char *cmd)
{
	if (error_code == SYNTAX_NEWLINE)
		code_2("newline");
	else if (error_code == SYNTAX_CLOSE_P)
		code_2(")");
	else if (error_code == SYNTAX_OPEN_P)
		code_2("(");
	else if (error_code == SYNTAX_PIPE)
		code_2("|");
	else if (error_code == SYNTAX_D_PIPE)
		code_2("||");
	else if (error_code == SYNTAX_PIPE_AMP)
		code_2("|&");
	else if (error_code == SYNTAX_AMP)
		code_2("&");
	else if (error_code == SYNTAX_D_AMP)
		code_2("&&");
	else if (error_code == SYNTAX_AMP_PIPE)
		code_2("||");
	else if (error_code == SYNTAX_CMD)
		code_2(cmd);
	else if (error_code == SYNTAX_ASP)
		code_2("\"");
	else
		errors_2(error_code, cmd);
}

void	errors_2(int error_code, char *cmd)
{
	if (error_code == SYNTAX_L_S_REDIR)
		code_2("<");
	else if (error_code == SYNTAX_S_ASP)
		code_2("\'");
	else if (error_code == SYNTAX_R_S_REDIR)
		code_2(">");
	else if (error_code == SYNTAX_L_D_REDIR)
		code_2("<<");
	else if (error_code == SYNTAX_R_D_REDIR)
		code_2(">>");
	else if (error_code == SYNTAX_BACKSLASH)
		code_2("\\");
	else if (error_code == SYNTAX_COLON)
		code_2(";");
	else if (error_code == HEREDOC_EOF)
	{
		bi_err("warning: here-document \
		delimited by end-of-file (wanted `", "", "");
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		ex_code(2);
	}
}

int	error_definer(char *cmd)
{
	char	err[3];
	int		i;
	int		j;

	i = 0;
	while (i < 3)
		err[i++] = '\0';
	i = 0;
	j = 0;
	if (!cmd)
		return (errors(SYNTAX_NEWLINE, NULL), 1);
	if (!cmd[j])
		return (errors(SYNTAX_NEWLINE, NULL), 1);
	j = ignore_spaces(cmd, j);
	if (cmd[j] == '\0')
		return (errors(SYNTAX_NEWLINE, NULL), 1);
	if (cmd[j] && j > 0 && cmd[j] == '|')
		return (errors(SYNTAX_PIPE, NULL), 1);
	if (cmd[j] && j == 0 && cmd[j] == '>' && cmd[j + 1] == '|')
		j = ignore_spaces(cmd, j + 2);
	while (cmd[j] && i < 2 && is_special_char(cmd[j]))
		err[i++] = cmd[j++];
	return (code_2(err), 1);
}
