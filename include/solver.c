/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/03/12 23:34:11 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int solver(char **final_cmds, t_info info, t_localenv *local, int fd_in_out[2], int in_out[2], t_builtin id)
{
	int		res;

	// if (cmd_list->down != NULL)
	// 	solver(cmd_list->down, info, local);
	// if (cmd_list && cmd_list->cmds)

		if (fd_in_out[1] == STDOUT_FILENO)
			res = exec_correct_builtin(final_cmds, fd_in_out[0], in_out[0], info, local, id);
		else if (fd_in_out[1] > STDOUT_FILENO)
			res = cd_output_exec(final_cmds, fd_in_out, in_out, info, local, id);
		// if (cmd_list && cmd_list->next)
		// {
		// 	while (cmd_list->next_type == D_PIPE && res == 0)
		// 		cmd_list = cmd_list->next;
		// 	if (cmd_list && cmd_list->next)
		// 		solver(cmd_list->next, info, local);
		// }
	// }
	// if (cmd_list && !cmd_list->cmds && cmd_list->next)
	// 	solver(cmd_list->next, info, local);
	return(res);
}

int	cd_output_exec(char **cmds, int *fd_in_out, int *in_out, t_info info, t_localenv *local, t_builtin id)
{
	int		fd;
	
	fd = dup(STDOUT_FILENO);
	dup2(fd_in_out[1], STDOUT_FILENO);
	close(fd_in_out[1]);
	exec_correct_builtin(cmds, fd_in_out[0], in_out[0], info, local, id);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	define_input(t_command *cmds, int *fd, int *heredocs, int *in)
{
	int		i;
char	*file;
		
	i = 0;
file = NULL;
	(*fd) = STDIN_FILENO;
	while ((cmds->cmds)[i])
	{
		if ((cmds->cmds)[i] == '<' && (cmds->cmds)[i + 1] != '<')
		{
			i++;
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open( file, O_RDWR);
			if (*fd < 0)
			{
				perror("minishell:");
				return ;
			}
			*in = IN_DOC; 
		}
		else if (cmds->cmds[i] == '<' && cmds->cmds[i + 1] == '<')
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
if (file != NULL)
		free(file);
}

void	define_output(t_command *cmds, int *fd, int *out)
{
	int		i;
	char	*file;
	
	i = 0;
	*fd = 1;
	while (cmds->cmds[i])
	{
		if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] != '>')
		{
			i++;
			if (*fd > 1)
				close(*fd);
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_TRUNC);
			close(*fd);
			*fd = open(file, O_RDWR|O_CREAT, 0666);
			*out = OUT_DOC; 
		}
		else if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] == '>')
		{
			i++;
			if (*fd > 1)
				close(*fd);
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_RDWR|O_APPEND|O_CREAT, 0660);
			*out = OUT_DOC; 
		}
		i++;
	}
	if (file != NULL)
		free(file);
}

char	*create_file_name(char *cmd, int *i)
{
	int		j;
	int		k;
	char	*file;
	
	k = 0;
	j = *i;
	*i = ignore_spaces(cmd, *i);
	while (cmd[j] && !ft_strchr("<>|& ", cmd[j]))
		j++;
	file = ft_calloc(j - (*i) + 2, sizeof(char));
	while (*i <= j)
	{
		file[k] = cmd[*i]; 
		(*i)++;
		k++;
	}
	return (file);
}

char	**clean_cmds(t_command *full_cmds)
{
char	*clean;
	char	**final_cmds;

	clean = clean_str(full_cmds->cmds);
	final_cmds = ft_split(clean, ' ');
	free(clean);
	return (final_cmds);
}

char	*clean_str(char *cmds)
{
	char	*clean;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	clean = ft_calloc(ft_strlen(cmds) + 1, sizeof(char));
	while (cmds[i])
	{
		if (cmds[i] == '<' || cmds[i] == '>') 
		{
			while(cmds[i] == '<' || cmds[i] == '>')
				i++;
			i = ignore_spaces(cmds, i);
			while(cmds[i] && cmds[i] != ' ')
		i++;
	}
	clean[j] = cmds[i];
		i++;
		j++;
	}
	return(clean);

}
