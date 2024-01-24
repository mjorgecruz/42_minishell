
/*This file contains builtin functions
as they will need extra functions we might need
to make new files.c for each of them and utils
*/

#include "minishell.h"

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