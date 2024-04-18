/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:49:36 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 17:16:09 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int     define_output_append(char *cmds, int *i, int *fd, int *out);
static int     define_output_redir(char *cmds, int *i, int *fd, int *out);

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
				return(free(file), pos);
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
	int 	pos;
	
    pos = 0;
	i = 0;
	*fd = 1;
	while (i < ft_strlen(cmds->cmds) && i < pos0 && cmds->cmds[i])
	{
		i = ignore_in_quotes(cmds->cmds, i);
		if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] != '>')
		{
            pos = define_output_redir(cmds->cmds, &i, fd, out);
			if (*fd <= -1)
                return(pos);
		}
		else if (cmds->cmds[i] == '>' && cmds->cmds[i + 1] == '>')
		{
            pos = define_output_append(cmds->cmds, &i, fd, out);
            if (*fd <= -1)
                return(pos);
		}
		if (cmds->cmds && cmds->cmds[i])
			i++;
	}
	return (i);
}

static int     define_output_redir(char *cmds, int *i, int *fd, int *out)
{
    char    *file;
    int     pos;

    file = NULL;
    pos = 0;
    (*i)++;
	if (cmds[*i] == '|')
		(*i)++;
	pos = *i;
	if (*fd > 1)
		close(*fd);
	if (file != NULL)
		free(file);
	file = create_file_name(cmds, i);
	*fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (*fd <= -1)
		return (free(file), pos);
	*out = OUT_DOC;
    return (free(file), pos);
}

static int     define_output_append(char *cmds, int *i, int *fd, int *out)
{
    char    *file;
    int     pos;
    
    file = NULL;
    (*i)+=2;
	pos = *i;
    if (*fd > 1)
		close(*fd);
	if (file != NULL)
		free(file);
	file = create_file_name(cmds, i);
	*fd = open(file, O_WRONLY|O_APPEND|O_CREAT, 0644);
	if (*fd < 0)
		return (free(file), pos);
	*out = OUT_DOC;
    return (free(file), pos);
}