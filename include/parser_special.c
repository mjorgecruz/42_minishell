/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/01/22 08:44:58 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
this parser receives the input string already cleared of any unfunctional quates double or single
the program should only come tho this point if the input is valid in any way
*/

/* ---- 
why do wee need to make a copy is it necessary? using const char * access is way more efficient if the only thing wee need is to see the values and not edit them*/
char	*parser_special(char *input)
{
    char    *output;    
    output = ft_strcpy(input);

    return(output);
}

/*simple CMDS*/

/* PIPES
comandos no geral nao te preocupes hoje eu ponho isto direitinho a funcionar lindo
*/ 

char **get_those_pipes(const char *input)
{
	int	i;

	while(is_space(input[i]))
		i++;
	//ifffff a partir de onde parou para a frente nao existir comando valido entao damos parse error (confirmar primeiro comando)
	/* seja logo pipe depois de whitspaces ou outra coisa qualquer tenho de parar
	enquanto ha espacos continua quando encontr algo diferente checka pra ver se e um comando se nao for manda erro e prompt back se for tenta executar
	*/
	
	while(input[i])
	{
		if (input[i] == '|' && is_space(input[i - 1]) && is_space(input[i + 1]))
		{
			//comandos antes e pipe a seguir da prompt back
			// quando encontrar tem de existir comando valido antes se for tudo em branco antes ou depois da merda
			//pipe valido distinguir processos com id
			//pegar no processo adicionar 
		}
		i++;	
	}
}

bool	is_space(char c)
{
	if((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}


/*

1- recebo a string
         nao me preocupo com quotes
2- equanto a string estiver em branco avanco nela
3- (option 1)Encontra algo (mal escrito) 
   (option 2)Encontra algo (bem escrito)
   (option 3)Nada encontra (ok)

3.1 (para comandos com pipe check mopdular de forma a checkar cada linha entre pipes ou atras e depois do pipe)
dai estrutura com token do comando e id para cada um deles apos este parser estar  corrido

3.2 option 2
Mesmo a encontrar algo bem escrito pode existir algo mal escrito a seguir ao primeiro comando manter a verificacao modular

 (tokenizar para o 4)
4 - tudo bem escrito, nao ha promptbacks nem merdas entao sim se for um so comando 
ele esta guardado ja tokenizado e pronto a ser executado ser forem varios estaram por ordens de prioridade do pipe.



estrutura ligadda a estrutura principal
- token type (identificador do comando para aceder na formater)
- string com todo o comando em si a ser introduzido na funcao que o corre.
- prioridade
- flag comand count atualizada na estrutura geral assim sabemos que se for apenas 1 nao temos de iniciar processos.
*/


