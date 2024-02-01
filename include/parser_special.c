/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/01 12:04:40 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return 1 if no trios of equals together found and 0  otherwise >>> ||| or <<< or &&&*/
int find_equal_trio_nospaces(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i); //ignora inside quotes e espacos
		if (is_special_char(str[i]))
		{
			if (find_same_trio(str, i))
				return (1);
			i++;
				
		}
	}
	return (0);
}

int	parser_special_first_module(const char *str)
{
	if(find_specials_outside_quotes(str) == false) //se nao encontrar specials deve dar logo ok e avancar com o programa return needed
	{
		printf("\n\x1b[32m[OK] ->\x1b[0m DIDNT FIND ANY SPECIAL SHOULD JUMP VERIFICATION OF THE NEXT STEPS AND RUN\n");
		return (1);
	}
	else if (find_equal_trio_nospaces(str)) // 0 advances didnt find 3 consecutives else 1 stops
	{
		printf("\n\x1b[31m[OK] ->\x1b[0m TRIO FOUND STOP\x1b[0m\n");
		return (0);
	}
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all in first module steps RTE\n");
	return (1);
}

void	parser_special(const char *str)
{
	if (parser_special_first_module(str)) //on return 1 continues on return 0 stops
	{
		return ;
	}
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