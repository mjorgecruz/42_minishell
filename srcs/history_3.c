/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:22:40 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 13:24:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	end_pipe_and(char *total_line)
{
	int		i;

	i = ft_strlen(total_line) - 1;
	while (i >= 0 && total_line[i] == ' ')
		i--;
	if (i >= 0 && (total_line[i] == '|' || total_line[i] == '&'))
		return (true);
	else
		return (false);
}

int	is_only_spaces(char *total_line)
{
	int		i;
	int		count;

	count = 0;
	i = ft_strlen(total_line) - 1;
	while (total_line[i] == ' ' && i >= 0)
	{
		i--;
		count++;
	}
	if (total_line[0] == ' ' || total_line[0] == '\0')
		return (count);
	else
		return (-1);
}

void	add_space_line(char **total_line, char *line_read)
{
	char	*garbage;

	garbage = *total_line;
	*total_line = ft_strjoin(*total_line, " ");
	free(garbage);
	garbage = *total_line;
	*total_line = ft_strjoin(*total_line, line_read);
	free(garbage);
}

int	open_parenthesis(char *total_line)
{
	int		i;
	int		count_open;

	i = 0;
	count_open = 0;
	while (total_line[i])
	{
		if (total_line[i] == '\'' || total_line[i] == '"')
			pass_quotes(total_line, &i);
		if (total_line[i] == '(')
			count_open++;
		if (total_line[i] == ')')
			count_open--;
		if (count_open < 0)
			return (-1);
		i++;
	}
	return (count_open);
}

char	*create_pc_name(t_localenv *local_env)
{
	char	*pwd;
	char	*name;
	char	*vai_fora;

	pwd = get_end_path(local_env);
	name = ft_strjoin("masoares&&luis-ffe@", "minishell:");
	vai_fora = name;
	name = ft_strjoin(name, pwd);
	free(vai_fora);
	free(pwd);
	return (name);
}
