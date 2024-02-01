/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/01 11:19:11 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*como vamos dar os exits disto? e frees?*/

int	parser_special_first_module(const char *str)
{
	if(find_specials_outside_quotes(str) == false) //se nao encontrar specials deve dar logo ok e avancar com o programa return needed
	{
		printf("\n\x1b[32m[OK] ->\x1b[0m DIDNT FIND ANY SPECIAL SHOULD JUMP VERIFICATION OF THE NEXT STEPS AND RUN\n");
		return (1);
	}
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all in first module steps RTE = -1\n");
	return (0);
}

void	parser_special(const char *str)
{
	if (parser_special_first_module(str))
		return ;
	//continua a correr 
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