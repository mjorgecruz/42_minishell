/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/31 12:49:06 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	parser_special(const char *str)
{
	parser_special_first_module(str);
	return ;
}


	//if(3 iguais consecutivos) sai erro
	
	//check from end final pipe or && . || or | and no speciesl before
	
	//primeiro se encontra pipe da erro   |
	
	//se o primeiro for rediect > ou <    --- cheks next tem de ser igual ao anterior ou | if [i-1] == >
	
	//erros de pipes | com espacos no meio 
	// && SEMPRE JUNTOS
	
	//verificar todos conjuntos de 3
		//   | 1st   >> > or << < or   
		// salta 1st pipe e verifica noamente da mesma forma |>> |>>
		// redirect combs >| >>  << > < 

/*
    printf("\x1b[31mThis is red text\x1b[0m\n");    // Red text
    printf("\x1b[32mThis is green text\x1b[0m\n");  // Green text
    printf("\x1b[33mThis is yellow text\x1b[0m\n"); // Yellow text
    printf("\x1b[34mThis is blue text\x1b[0m\n");   // Blue text
*/