/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:49 by masoares          #+#    #+#             */
/*   Updated: 2024/01/22 07:58:39 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* estrutura geral que vai ligar a outras estruturas
 e dar acesso a toda a informacao*/

typedef struct s_data
{
	char *input;
}	t_data;

/*funcao para inicializar essa estrutura em modo static 
assim limpa automatiamente e nao temos de mallocar*/

t_data	mini_data_init()
{
	satatic t_data shell;
	return(&shell)
}

int	main(int ac, char **av)
{
	char	*input;
	char	*clean_input;
	char	*paths;
	
	(void) ac;
	(void) av;
	//(void) env;
	
	paths = getenv("PATH");
	input = NULL;
	clear_terminal(paths);
	while(1)
	{
		input = get_line(input);
		if (input != NULL)
		{
			rl_on_new_line();
			clean_input = ft_parser(input);
			command_executer(clean_input, paths);
			//printf("%s", clean_input);
			//rl_redisplay();
			free(input);
			free(clean_input);
		}
	}
}

void	clear_terminal(char *paths)
{
	char	**cmd;
	int		pid;
	char	**p_path;
	int		i;
	
	
	i = 0;
	p_path = ft_split(paths, ':');
	cmd = ft_split("clear", ' ');
	while(access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
	{
		p_path[i] = ft_strjoin(p_path[i], "/");
		cmd[0] = ft_strjoin(p_path[i], "clear");
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);
	waitpid(pid, NULL, 0);
	free_split(cmd);
	free_split(p_path);
	return ;
}
