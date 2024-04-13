/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:25:24 by masoares          #+#    #+#             */
/*   Updated: 2024/04/14 00:08:07 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	add_partials(char **heredoc, char *str)
{
	char	*heredoc_line;
	
	heredoc_line = readline("> ");
	if (heredoc_line == NULL)
	{
		*heredoc = ft_calloc(1, sizeof(char));
		return (errors(HEREDOC_EOF, str));
	}
	while (ft_strcmp(str, heredoc_line))
	{
		add_newline_line(heredoc, heredoc_line);
		heredoc_line = readline("> ");
		if (heredoc_line == NULL)
			return (errors(HEREDOC_EOF, str));
	}
	free(heredoc_line);
	if (!*heredoc)
	{
		*heredoc = ft_calloc(2, sizeof(char));
		*heredoc[0] = '\n';
	}	
	else
		*heredoc = ft_strjoin_2(*heredoc, "\n");
}


void	add_newline_line(char **total_line, char *line_read)
{
	if (*total_line != NULL)
	{
		*total_line = ft_strjoin_2(*total_line, "\n");
		*total_line = ft_strjoin_2(*total_line, line_read);
	}
	else
		*total_line = line_read;
}
char	*ft_strjoin_2(char *s1, char const *s2)
{
	size_t	i1;
	size_t	i2;
	size_t	j;
	char	*s;

	j = 0;
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	s = (char *) malloc (sizeof(char) * (i1 + i2 + 1));
	if (s == NULL)
		return (NULL);
	while (s1 && j < i1)
	{
		s[j] = s1[j];
		j++;
	}
	while (j < i1 + i2)
	{
		s[j] = s2[j - i1];
		j++;
	}
	s[j] = '\0';
	return (free(s1), s);
}
