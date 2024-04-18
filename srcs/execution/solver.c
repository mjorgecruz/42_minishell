/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 01:29:43 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int solver(char **final_cmds, t_info info, t_cmd_info *cmd_info)
{
	int		res;
	int		fd;
	
	res = 0;
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
	int		res;
	
	res = 0;
	fd = dup(STDOUT_FILENO);
	dup2(cmd_info.fd_in_out[1], STDOUT_FILENO);
	close(cmd_info.fd_in_out[1]);
	res = exec_correct_builtin(cmds, info, id, cmd_info);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (res);
}

int	define_input(t_command *cmds, int *fd, int *heredocs, int *in)
{
	int		i;
	char	*file;
	int 	pos;
		
	i = 0;
	file = NULL;
	(*fd) = dup(STDIN_FILENO);
	while ((cmds->cmds)[i] != 0)
	{
		i = ignore_in_quotes(cmds->cmds, i);
		if ((cmds->cmds)[i] == '<' && (cmds->cmds)[i + 1] != '<')
		{
			i++;
			pos = i;
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_RDONLY);
			if (*fd < 0)
				return(pos);
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
	return (i);
}

int	define_output(t_command *cmds, int *fd, int *out, int pos0)
{
	int		i;
	char	*file;
	int 	pos;
	
	i = 0;
	*fd = 1;
	file = NULL;
	while (i < ft_strlen(cmds->cmds) && i < pos0 && cmds->cmds[i])
	{
		i = ignore_in_quotes(cmds->cmds, i);
		if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] != '>')
		{
			i++;
			if (cmds->cmds[i] == '|')
				i++;
			pos = i;
			if (*fd > 1)
				close(*fd);
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_TRUNC);
			close(*fd);
			*fd = open(file, O_RDWR|O_CREAT, 0666);
			if (*fd == -1)
				return (pos);
			*out = OUT_DOC; 
		}
		else if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] == '>')
		{
			i+=2;
			pos = i;
			if (*fd > 1)
				close(*fd);
			if (file != NULL)
				free(file);
			file = create_file_name(cmds->cmds, &i);
			*fd = open(file, O_WRONLY|O_APPEND|O_CREAT, 0660);
			if (*fd < 0)
				return (pos) ;
			*out = OUT_DOC; 
		}
		if (cmds->cmds && cmds->cmds[i])
			i++;
	}
	if (file != NULL)
		free(file);
	return (i);
}

char	*create_file_name(char *cmd, int *i)
{
	int		j;
	char	*file;
	char	*trav;
	char	*garbage;
	
	file = ft_strdup("");
	trav = ft_calloc(2, sizeof(char));
	*i = ignore_spaces(cmd, *i);
	j = *i;
	while (cmd[j] && !ft_strchr("<>|& \t\n", cmd[j]))
	{
		if (ft_strchr("\"\'", cmd[*i]))
		{
			j++;
			while (cmd[j] && cmd[j] != cmd[*i])
			{
				garbage = file;
				trav[0] = cmd[j];
				file = ft_strjoin(file, trav);
				free(garbage);
				j++;
			}
			j++;
		}
		else
		{
			garbage = file;
			trav[0] = cmd[j];
			file = ft_strjoin(file, trav);
			free(garbage);
			j++;
		}
	}
	*i = j;
	return (free(trav), file);
}

char	**clean_cmds(t_command *full_cmds, t_localenv *local)
{
	char	*clean;
	char	*clean_2;
	char 	**trav;
	char	**final_cmds;
	int		i;

	clean = clean_str(full_cmds->cmds);
	clean_2 = expander_heredocs(clean, local); 
	trav = ft_split_ignore_quotes(clean_2, " \t\n");
	i = 0;
	while (trav && trav[i] != 0)
		i++; 
	final_cmds = (char **)malloc(sizeof(char *) * (i + 1));
	final_cmds[i] = 0;
	i = 0;
	while (trav[i])
	{
		final_cmds[i] = master_expander_out(trav[i], local);
		i++;
	}
	free(clean_2);
	free_split(trav);
	return (final_cmds);
}

char	*clean_str(char *cmds)
{
	char	*clean;
	int		i;
	int		j;
	char	c;
	
	i = 0;
	j = 0;
	if (!cmds)
		return (NULL);
	clean = ft_calloc(ft_strlen(cmds) + 1, sizeof(char));
	while  (cmds[i])
	{
		if  (cmds[i] == '\"' || cmds[i] == '\'')
		{
			c = cmds[i];
			clean[j] = cmds[i];
			i++;
			j++;
			while (cmds[i] && cmds[i] != c)
			{
				clean[j] = cmds[i];
				i++;
				j++;
			}
		}
		if (cmds[i] == '<' || cmds[i] == '>') 
		{
			while(cmds[i] == '<' || cmds[i] == '>' || cmds[i] == '|')
				i++;
			i = ignore_spaces(cmds, i);
			i = ignore_in_quotes(cmds, i);
			while(cmds[i] && cmds[i] != ' ')
				i++;
			if (!cmds[i])
				break;
		}
		clean[j] = cmds[i];
		i++;
		j++;
	}
	clean[j] = 0;
	return (clean);
}
