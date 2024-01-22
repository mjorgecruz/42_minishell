/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:49 by masoares          #+#    #+#             */
/*   Updated: 2024/01/22 14:53:22 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_data	*mini_data_init(void)
// {
// 	static t_data shell;
// 	return (&shell);
// }

int	main(int ac, char **av)
{
	char	*input;
	char	*paths;
	
	(void) ac;
	(void) av;
	//(void) env;
	
	paths = getenv("PATH");
	clear_terminal(paths);
	input = NULL;
	while(1)
	{
		input = get_line(input);
		if (input != NULL && *input)
		{
			rl_on_new_line();
			ft_parser(input);
			if (input == NULL)
				return (1);
			command_executer(input, paths);
			//printf("%s", clean_input);
			//rl_redisplay();
			//free(input);
			free(input);
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
