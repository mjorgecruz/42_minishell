/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:02 by masoares          #+#    #+#             */
/*   Updated: 2024/02/15 13:23:57 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains all error handling functions*/

#include "../../includes/minishell.h"

void	errors(int error_code, char *cmd)
{
	if (error_code == SYNTAX_NEWLINE)
		printf("minishell:syntax error near unexpected token `newline'\n");
	else if (error_code == SYNTAX_CLOSE_P)
		printf("minishell:syntax error near unexpected token `)'\n");
	else if (error_code == SYNTAX_OPEN_P)
		printf("minishell:syntax error near unexpected token `('\n");
	else if (error_code == SYNTAX_PIPE)
		printf("minishell:syntax error near unexpected token `|'\n");
	else if (error_code == SYNTAX_D_PIPE)
		printf("minishell:syntax error near unexpected token `||'\n");
	else if (error_code == SYNTAX_PIPE_AMP)
		printf("minishell:syntax error near unexpected token `|&'\n");
	else if (error_code == SYNTAX_AMP)
		printf("minishell:syntax error near unexpected token `&'\n");
	else if (error_code == SYNTAX_D_AMP)
		printf("minishell:syntax error near unexpected token `&&'\n");
	else if (error_code == SYNTAX_AMP_PIPE)
		printf("minishell:syntax error near unexpected token `||'\n");
	else if (error_code == SYNTAX_CMD)
		printf("minishell:syntax error near unexpected token `%s'\n", cmd);
	else if (error_code == SYNTAX_ASP)
		printf("minishell:syntax error near unexpected token `\"'\n");
	else
		errors_2(error_code, cmd);
}

void	errors_2(int error_code, char *cmd)
{
	if (error_code == SYNTAX_L_S_REDIR)
		printf("minishell:syntax error near unexpected token `<'\n");
	else if (error_code == SYNTAX_S_ASP)
		printf("minishell:syntax error near unexpected token `\''\n");
	else if (error_code == SYNTAX_R_S_REDIR)
		printf("minishell:syntax error near unexpected token `>'\n");
	else if (error_code == SYNTAX_L_D_REDIR)
		printf("minishell:syntax error near unexpected token `<<'\n");
	else if (error_code == SYNTAX_R_D_REDIR)
		printf("minishell:syntax error near unexpected token `>>'\n");
	else if (error_code == SYNTAX_BACKSLASH)
		printf("minishell:syntax error near unexpected token `\\'\n");
	else if (error_code == SYNTAX_COLON)
		printf("minishell:syntax error near unexpected token `;'\n");
	else if (error_code == HEREDOC_EOF)
		printf("minishell:warning: here-document delimited\
by end-of-file (wanted `%s')\n", cmd);
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
	return \
	(printf("minishell:syntax error near unexpected token `%s'\n", err), 1);
}

