/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:19:08 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 13:55:48 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

static int	adjust_shlvl(char **environ);

int	main(void)
{
	char		*input;
	char		**heredocs;
	int			i;
	t_localenv	*local_env;

	adjust_shlvl(__environ);
	local_env = env_init(__environ);
	input = NULL;
	i = 0;
	g_signal = 0;
	while (1)
	{
		input = get_line(input, &heredocs, local_env);
		if (input == NULL)
			continue ;
		if (input != NULL && *input && input[ft_strlen(input) - 1] != 0x03)
		{
			if (input[ignore_spaces(input, i)])
				general_executer(input, &heredocs, local_env);
			input = NULL;
		}
		if (input != NULL)
			free(input);
	}
}

static int	adjust_shlvl(char **environ)
{
	int		i;
	int		shlvl;
	char	*intoa;
	char	*sh;
	int		j;

	intoa = NULL;
	i = -1;
	j = -1;
	while (environ[++i])
	{
		if (!ft_strncmp("SHLVL", environ[i], 5))
		{
			shlvl = ft_atoi(&(environ[i][6]));
			intoa = ft_itoa(shlvl + 1);
			sh = ft_strjoin("SHLVL=", intoa);
			while (sh[++j])
				environ[i][j] = sh[j];
			environ[i][j] = 0;
			free(intoa);
			free(sh);
			break ;
		}
	}
	return (i);
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
	while (access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
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
