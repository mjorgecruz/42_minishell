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


t_builtin get_builtin_id(const char *str) /*all lowercase?  no aspens?? XD*/
{
	if (strcmp(str,"cd"))
		return (CD);
	if (strcmp(str,"export"))
		return (EXPORT);
	if (strcmp(str,"env"))
		return (ENV);
	if (strcmp(str,"echo"))
		return (ECHO);
	if (strcmp(str,"unset"))
		return (UNSET);
	if (strcmp(str,"exit"))
		return (EXIT);
	if (strcmp(str,"pwd"))
		return (PWD);
	return (UNDEFINED);
}
/*having a formater returning an enum makes the functions shorter and we can use this in other parts*/
/*after strcomp doing numbers comparision is way faster thats why i made  it like this*/
void	exec_correct_builtin(t_token **cdm_list, t_builtin id)
{
	if (id == UNDEFINED)
		/*go to execve*/
	if (id == CD)
		/*go to builtin*/
	if (id == ECHO)
		/*go to builtin*/
	if (id == PWD)
		/*go to builtin*/
	if (id == EXIT)
		/*go to builtin*/
	if (id == EXPORT)
		/*go to builtin*/
	if (id == ENV)
		/*go to builtin*/
	if (id == UNSET)
		/*go to builtin*/
}


void	commands_sorter(t_token **cmd_list)
{
	int i;
	t_builtin id;
/*this get builtin id should be in a loop checking for all the first comand to be executed
and send it to execute on the folowing function that takes in the id
*/
	id = get_builtin_id("cd"); /*we shoul only send the 
	correct string with thecomand from the structure to this function*/

	i = 0;
	while (cmd_list[i]->cmds[0].cmds[0]) /*is valid and not null comparing just the first token*/

	/*
	make some kind of formater chosing what comand to execute if it is the corresponding symbol
	not being part of any it jumps all to the last one and goes to execve
	*/ 
}
/*do i have to handle empoty null or will always reach me with something*/
/*i could be using an enum flag*/

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

int	command_echo()
{
	printf(...)
}

int	command_cd(char *line, char *paths)
{
}

int	comand_pwd()
{
	
}
int	command_export()
{
	
}
int	command_unset()
{
	
}
int	command_env()
{
	
}
int	command_exit()
{
	
}
