/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/03/07 11:23:07 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int solver(t_token *cmd_list, t_info info, t_localenv *local)
{
	int		fd_in_out[2];
	int 	in_out[2];
		
	in_out[0] = UNDEF;
	in_out[1] = UNDEF;
	fd_in_out[0] = 0;
	fd_in_out[1] = 1;
	if (cmd_list->down != NULL)
		solver(cmd_list->down, info, local);
	while (cmd_list && cmd_list->cmds)
	{
		define_input(cmd_list->cmds, &fd_in_out[0], &info.pos_heredoc, &in_out[0]);
		if (fd_in_out[0] == -1)
			return (-1);
		//printf(in:  fd %d, heredoc %d, in %d\n", fd_in, heredocs, in);
		define_output(cmd_list->cmds, &fd_in_out[1], &in_out[1]);
		//printf("out: fd %d, in %d\n", fd_out, out);
		if (fd_in_out[1] == STDOUT_FILENO)
			exec_correct_builtin(cmd_list->cmds, fd_in_out[0], in_out[0], info, local);
		else if (fd_in_out[1] > STDOUT_FILENO)
			cd_output_exec(cmd_list->cmds, fd_in_out, in_out, info, local);
		cmd_list = cmd_list->next;
	}
	return(1);
}

int	cd_output_exec(t_command *cmds, int *fd_in_out, int *in_out, t_info info, t_localenv *local)
{
	int		fd;
	
	fd = dup(STDOUT_FILENO);
	dup2(fd_in_out[1], STDOUT_FILENO);
	close(fd_in_out[1]);
	exec_correct_builtin(cmds, fd_in_out[0], in_out[0], info, local);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	define_input(t_command *cmds, int *fd, int *heredocs, int *in)
{
	int		i;
		
	i = 0;
	(*fd) = STDIN_FILENO;
	while (cmds[i].cmds != NULL)
	{
		if (cmds[i].type == S_REDIR_IN)
		{
			*fd = open( cmds[i + 1].cmds[0], O_RDWR);
			if (*fd < 0)
			{
				perror("minishell:");
				return ;
			}
			*in = IN_DOC; 
		}
		if (cmds[i].type == D_REDIR_IN)
		{
			if (*fd > -1)
			{
				close(*fd);
				*fd = -1;
			}
			(*heredocs)++;
			*in = HEREDOC;
		}
		i++;
	}
}

void	 define_output(t_command *cmds, int *fd, int *out)
{
	int		i;
		
	i = 0;
	*fd = -1;
	while (cmds[i].cmds)
	{
		if (cmds[i].type == S_REDIR_OUT)
		{
			if (*fd > -1)
				close(*fd);
			*fd = open(cmds[i + 1].cmds[0], O_TRUNC);
			close(*fd);
			*fd = open(cmds[i + 1].cmds[0], O_RDWR|O_CREAT, 0666);
			*out = OUT_DOC; 
		}
		if (cmds[i].type == D_REDIR_OUT)
		{
			if (*fd > -1)
				close(*fd);
			*fd = open(cmds[i + 1].cmds[0], O_RDWR|O_APPEND|O_CREAT, 0660);
			*out = OUT_DOC; 
		}
		i++;
	}
}
