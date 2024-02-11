/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/02/11 18:27:14 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_counter(char *total_line)
{
	int	i;
	int	heredocs;

	heredocs = 0;
	i = 0;
	while (total_line[i])
	{
		if (total_line[i] == '<' && total_line[i - 1] == '<')
			heredocs++;
		i++;
	}
	return (heredocs);
}

char	**heredoc_writer(char *total_line, int heredocs)
{
	//malloc de strings igual ao numero de heredocs + 1
	//ler da readline e adicionar a string ate encontrar a primeira palavra depois do heredoc
	//adicionar um "/n" entre cada frase
	// ultimo elemento NULL
}