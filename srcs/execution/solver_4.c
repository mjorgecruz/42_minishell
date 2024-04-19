/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:58:49 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 14:00:44 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*is_file(int *i, int *fd, int *in, t_command *cmds)
{
	char	*file;
	int		pos;

	(*i)++;
	pos = (*i);
	file = create_file_name(cmds->cmds, i);
	*in = IN_DOC;
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		*i = pos;
		return (free(file), NULL);
	}
	return (file);
}

static void	is_heredoc(int *fd, int *heredocs, int *in, int *i)
{
	if (*fd > STDIN_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
	(*heredocs)++;
	*in = HEREDOC;
	(*i)++;
}

int	define_input(t_command *cmds, int *fd, int *heredocs, int *in)
{
	int		i;
	char	*file;

	i = 0;
	file = NULL;
	(*fd) = dup(STDIN_FILENO);
	while ((cmds->cmds)[i] != 0)
	{
		i = ignore_in_quotes(cmds->cmds, i);
		if ((cmds->cmds)[i] == '<' && (cmds->cmds)[i + 1] != '<')
		{
			if (file != NULL)
				free(file);
			file = is_file(&i, fd, in, cmds);
			if (file == NULL)
				return (i);
		}
		else if (cmds->cmds[i] == '<' && cmds->cmds[i + 1] == '<')
			is_heredoc(fd, heredocs, in, &i);
		i++;
	}
	if (file != NULL)
		free(file);
	return (i);
}
