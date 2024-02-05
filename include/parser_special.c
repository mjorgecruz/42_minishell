/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/01 15:39:32 by luis-ffe         ###   ########.fr       */
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
	else if (is_invalid_start_sign(str))
	{
		printf("\n\x1b[31m[KO] ->\x1b[0m INVALID START\x1b[0m\n");
		return (0);
	}
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all firstmodule\n");
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

/*
***************************** Funcionalidades ja implementadas *************************

 ok -> Nao encontrando sinais avanca direto.
 ok -> Iguais consecutivos dar merda.
 ok -> Tratado >> <<  > <   >|    todas as condicoes iniciais que funcionam com um simbolo ou dois
 ok -> Da erro caso nao corresponda a uma combinacao de simbolos valida no inicio.
 ok -> Tem de ter comando valido na frente que nao seja especial nem fim da string.
 
**************************************************************************************
 

check from end final pipe or && . || or | and no speciesl before

erros de pipes | com espacos no meio 
&& SEMPRE JUNTOS
	
	//verificar todos conjuntos de 3
		//   | 1st   >> > or << < or   
		// salta 1st pipe e verifica noamente da mesma forma |>> |>>
		// redirect combs >| >>  << > < 
*/
