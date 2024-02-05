/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/05 12:17:37 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_special_first_module(const char *str)
{
	if(find_specials_outside_quotes(str) == false) //se nao encontrar specials deve dar logo ok e avancar com o programa return needed
	{
		printf("\n\x1b[32m[OK] ->\x1b[0m DIDNT FIND ANY SPECIAL\n");
		return (1);
	}
	else if (find_equal_trio_nospaces(str)) // 0 advances didnt find 3 consecutives else 1 stops
	{
		printf("\n\x1b[31m[KO] ->\x1b[0m TRIO FOUND STOP\x1b[0m\n");
		return (0);
	}
	else if (check_invalid_specialcount(str, 0))
	{
		printf("\n\x1b[31m[KO] ->\x1b[0m >4 Sid w/wo spaces -> FOUND STOP\x1b[0m\n");
		return (0);
	}
	// else if (is_invalid_start_sign(str))
	// {
	// 	printf("\n\x1b[31m[KO] ->\x1b[0m INVALID START\x1b[0m\n");
	// 	return (0);
	// }
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all firstmodule\n");
	return (1);
}

bool	parser_special(const char *str)
{
	if (!parser_special_first_module(str)) //on return 1 continues on return 0 stops
	{
		return (false);
	}
	return (true);
}

/*
*****************************Funcionalidades ja implementadas*************************

 ok -> Nao encontrando sinais avanca direto.
 ok -> Iguais consecutivos dar merda.
 
**************************************************************************************
 
primeiro se encontra pipe da erro   |
check from end final pipe or && . || or | and no speciesl before
se o primeiro for rediect > ou <    --- cheks next tem de ser igual ao anterior ou | if [i-1] == >
erros de pipes | com espacos no meio 
&& SEMPRE JUNTOS
	
	//verificar todos conjuntos de 3
		//   | 1st   >> > or << < or   
		// salta 1st pipe e verifica noamente da mesma forma |>> |>>
		// redirect combs >| >>  << > < 
*/
