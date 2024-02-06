/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/06 16:36:34 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_special_first_module(char *str)
{
	int		specialcount;

	specialcount = -1;
	specialcount = check_invalid_specialcount(str, 0);
	if(find_specials_outside_quotes(str) == false)
		return (1);
	else if (find_equal_trio_nospaces(str))
		return (0);
	else if (specialcount >=0)
	{
		error_definer(&str[specialcount]);
		return (0);
	}
	else if (is_invalid_start_sign(str))
	{
		
		return (0);
	}
	return (1);
}

bool parser_special_module_two(char *str)
{
	if (mid_parser_iteration(str))
	{
		return (true);
	}
	return false;
}

/* primeiro modulo retornando true deve ser executado o modulo 2, que se tambem retornar verdadeiro significa que passou no parser */
bool	parser_special(char *str)
{
	if (parser_special_first_module(str) == false) //on return true continues on false stops(error)
		return false;
	if (parser_special_module_two(str) == false) //on return true continues on false stops(error)
		return false;
	return true;
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
