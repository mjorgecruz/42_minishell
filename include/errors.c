/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:22:02 by masoares          #+#    #+#             */
/*   Updated: 2024/02/06 16:20:46 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains all error handling functions*/

#include "minishell.h"

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

void errors_2(int error_code, char *cmd)
{
	(void) cmd;
	if (error_code == SYNTAX_L_S_REDIR)
		printf("minishell:syntax error near unexpected token `<'\n");
	if (error_code == SYNTAX_R_S_REDIR)
		printf("minishell:syntax error near unexpected token `>'\n");
	if (error_code == SYNTAX_L_D_REDIR)
		printf("minishell:syntax error near unexpected token `<<'\n");
	if (error_code == SYNTAX_R_D_REDIR)
		printf("minishell:syntax error near unexpected token `>>'\n");
}

int error_definer(char *cmd)
{
	char	err[3];
	int		i;
	
	i = 0;
	while (i < 3)
		err[i++] = '\0';
	i = 0;
	while (i < 2 && is_special_char(cmd[i]))
	{
		err[i] = cmd[i];
		i++;
	}
	printf("minishell:syntax error near unexpected token `%s'\n", err);
	return (1);
}

int	wrong_syntax(char *line)
{
	(void) line;
	// int i;
	// i = 0;
	// if (line[i] == '&' && line[i + 1] != line[i])
	// {
	// 	errors(SYNTAX_AMP, NULL);
	// 	return (0);
	// }
	// else if (line[i] == '|' && line[i + 1] != line[i])
	// {
	// 	if  ()
	// }
	// else if (line[i] == '>' && line[i + 1] != line[i])
	// {
	// 	if  ()
	// }
	// else if (line[i] == '<' && line[i + 1] != line[i])
	// {
	// 	if  ()
	// }
	// else
		
	return (0);
}
