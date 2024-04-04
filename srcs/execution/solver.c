/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/04/04 14:14:56 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int solver(char **final_cmds, t_info info, t_cmd_info *cmd_info)
{
	int		res;
	int		fd;
	
	res = 1; //aded this shit this was not initialized check it
	if (cmd_info->fd_in_out[0] != STDIN_FILENO)
	{
		fd = dup(STDIN_FILENO);
		dup2(cmd_info->fd_in_out[0], STDIN_FILENO);
		close(cmd_info->fd_in_out[0]);
	}
	if (cmd_info->fd_in_out[1] == STDOUT_FILENO)
		res = exec_correct_builtin(final_cmds, info, cmd_info->id, *cmd_info);
	else if (cmd_info->fd_in_out[1] > STDOUT_FILENO)
		res = cd_output_exec(final_cmds, info, cmd_info->id, *cmd_info);
	if (cmd_info->fd_in_out[0] != STDIN_FILENO)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (res);
}

int	cd_output_exec(char **cmds, t_info info, t_builtin id, t_cmd_info cmd_info)
{
	int		fd;
	
	fd = dup(STDOUT_FILENO);
	dup2(cmd_info.fd_in_out[1], STDOUT_FILENO);
	close(cmd_info.fd_in_out[1]);
	exec_correct_builtin(cmds, info, id, cmd_info);
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
	while ((cmds->cmds)[i] != 0)
	{
		if ((cmds->cmds)[i] == '<' && (cmds->cmds)[i + 1] != '<')
		{
			i++;
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_RDWR);
			if (*fd < 0)
			{
				perror("minishell");
				return ;
			}
			*in = IN_DOC; 
		}
		else if (cmds->cmds[i] == '<' && cmds->cmds[i + 1] == '<')
		{
			if (*fd > STDIN_FILENO)
			{
				close(*fd);
				*fd = -1;
			}
			(*heredocs)++;
			*in = HEREDOC;
			i++;
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
	file = NULL;
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
			if (*fd < 0)
			{
				perror("minishell");
				return ;
			}
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
	*i = ignore_spaces(cmd, *i);
	j = *i;
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

char	**clean_cmds(t_command *full_cmds, t_localenv *local)
{
	char	*clean;
	char 	*trav;
	char	**final_cmds;

	clean = clean_str(full_cmds->cmds);
	trav = master_expander_out(clean, local);
	final_cmds = ft_split_ignore_quotes(trav, " ");
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
	return (clean);

}
