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

/*assumir que 1 is true ou seja passou nestes testes e deve avancar para modulo 2*/

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
		printf("\n\x1b[31m[KO] ->\x1b[0m >4 Signals w/wo spaces FOUND -> STOP\x1b[0m\n");
		return (0);
	}
	else if (is_invalid_start_sign(str)) //aquelas merdaas todas de inicio para checkar as combinacoes validas com comando valido na frente
	{
		printf("\n\x1b[31m[KO] ->\x1b[0m INVALID START\x1b[0m\n");
		return (0);
	}
	printf("\n\x1b[32m[OK] ->\x1b[0m Passed all firstmodule\n");
	return (1);
}

<<<<<<< HEAD
bool	parser_special(const char *str)
{
	if (!parser_special_first_module(str)) //on return 1 continues on return 0 stops
	{
		return (false);
	}
	return (true);
=======
bool parser_special_module_two(const char *str)
{
	if (mid_parser_iteration(str))
	{
		printf("\n\x1b[32m[OK] ->\x1b[0m VALID -> M2\n");
		return (true);
	}
	printf("\n\x1b[31m[KO] ->\x1b[0m INVALID ->  M2\x1b[0m\n");
	return false;
}

/* primeiro modulo retornando true deve ser executado o modulo 2, que se tambem retornar verdadeiro significa que passou no parser */
bool	parser_special(const char *str)
{
	if (parser_special_first_module(str) == false) //on return true continues on false stops(error)
		return false;
	if (parser_special_module_two(str) == false) //on return true continues on false stops(error)
		return false;
	return true;
>>>>>>> ba66e1cbb78874b12f55260f6246021d203b00f1
}

/*
***************************** Funcionalidades ja implementadas first module *************************

 ok -> Nao encontrando sinais avanca direto.
 ok -> Iguais consecutivos dar merda.
 ok -> Tratado >> <<  > <   >|    todas as condicoes iniciais que funcionam com um simbolo ou dois
 ok -> Da erro caso nao corresponda a uma combinacao de simbolos valida no inicio.
 ok -> Tem de ter comando valido na frente que nao seja especial nem fim da string.
 ok -> erros de pipes | com espacos no meio 
 ok -> && SEMPRE JUNTOS
	  //verificar todos conjuntos de 3
	     	//   | 1st   >> > or << < or   
	 		//   |>> |>>
			// redirect combs >| >>  << > < 
 
**************************************************************************************
 
NOT YET / NOT SURE    ->     check from end final pipe or && . || or | and no speciesl before

*/
