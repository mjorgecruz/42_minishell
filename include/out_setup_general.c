/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/01/24 10:46:41 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*fix aspens??  here or in previous steps? maybe flag it*/
t_builtin get_builtin_id(const char *str) 
{
	if (strcmp(str, "cd"))
		return (CD);
	if (strcmp(str, "export"))
		return (EXPORT);
	if (strcmp(str, "env"))
		return (ENV);
	if (strcmp(str, "echo"))
		return (ECHOS);
	if (strcmp(str, "unset"))
		return (UNSET);
	if (strcmp(str, "exit"))
		return (EXIT);
	if (strcmp(str, "pwd"))
		return (PWD);
	return (UNDEFINED);
}

//sets the struct id for the comand using the enums for builtins.

void	set_id_flag_cmd(t_token **cmd_list)
{
	int	i;
	int	j;

	i = -1;
	while (cmd_list[++i] != NULL)
	{
		j = -1;
		while (cmd_list[i]->cmds[++j].cmds[0] != NULL)
			cmd_list[i]->cmds[j].id = get_builtin_id(cmd_list[i]->cmds[j].cmds[0]);
	}
	return ;
}

/*
void	exec_correct_builtin(t_token **cdm_list, t_builtin id)
{
//comand runner functions be inside the return
	if (id == UNDEFINED)
		//command_execve();
	else if (id == CD)
		//command_cd();
	else if (id == ECHOS)
		//command_echo();
	else if (id == PWD)
		//command_pwd();
	else if (id == EXIT)
		//command_exit();
	if (id == EXPORT)
		//command_export();
	if (id == ENV)
		//command_env();
	if (id == UNSET)
		//command_unset();
}
*/


/*
void	commands_sorter(t_token **cmd_list)
{

}
*/


int	command_execve(char *line, char *paths)
{
	char	**cmd;
	int		pid;
	char	**p_path;
	int		i;

	i = 0;
	p_path = ft_split(paths, ':');
	cmd = ft_split(line, ' ');
	ft_bzero(line, ft_strlen(line));
	line = ft_strjoin(line, cmd[0]);
	p_path[i] = ft_strjoin(p_path[i], "/");
	cmd[0] = ft_strjoin(p_path[i], cmd[0]);
	while (access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
	{
		p_path[i] = ft_strjoin(p_path[i], "/");
		cmd[0] = ft_strjoin(p_path[i], line);
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);
	waitpid(pid, NULL, 0);
	return (free(line), free_split(p_path), free_split(cmd), 1);
}


int	comand_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

/*

int	command_echo(t_token **cmd_list)
{
}

int	command_cd(t_token **cmd_list)
{
}

int	command_export(t_token **cmd_list)
{
	
}
int	command_unset(t_token **cmd_list)
{
	
}
int	command_env(t_token **cmd_list)
{
	
}

int	command_exit(t_token **cmd_list) //will we be handling the extra numbers after exit comand?
{
	 //if exit has more than 2 arguments or 1 if not handling numbers
	 	//[print tooo many arguments error]
		//and prompts back
	//if handling confirm if second is numeric and error if not numeric
		//if ALL OK THEN WE PRINT "exit"
		//we free and close
}

*/
