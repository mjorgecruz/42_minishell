/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:09:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/04 17:15:54 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	change_directory(const char *path)
{
	int error;
	
	if (chdir(path) == -1)
	{
		error = errno;
		//ft_printf("%d", error);
		return (error);
	}
	return (EXIT_SUCCESS);
}

char	*get_home_directory(t_localenv *local)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME", local->content);
	if (!home_dir)
		return (NULL);
	return (home_dir);
}

char	*get_previous_directory(t_localenv *local)
{
	char	*prev_dir;

	prev_dir = ft_getenv("OLDPWD", local->content);
	if (!prev_dir)
		return (NULL);
	return (prev_dir);
}

int	update_directories(t_localenv *local, char *cwd)
{
	if (ft_setenv("OLDPWD", ft_getenv("PWD", local->content), local) == -1)
		return (-1);
	if (ft_setenv("PWD", cwd, local) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

int	command_cd(char **cmds, t_localenv *local)
{
	char	*target_dir;
	char	cwd[PATH_MAX];
	int err;
	
	if (cmds[2] != NULL)
		return (builtin_errors("cd: too many arguments", "", ""));
	if (cmds[1] == NULL || cmds[1][0] == '\0')
		target_dir = get_home_directory(local);
	else if (strcmp(cmds[1], "-") == 0)
		target_dir = get_previous_directory(local);
	else
		target_dir = cmds[1];

	if (!target_dir)
		return (EXIT_FAILURE);
	err = change_directory(target_dir);
	if (err == 13)
		return (builtin_errors("cd: ", "", ": Permission denied\n"));
	if (err == 2)
		return (builtin_errors("cd: ", cmds[1], ": no such file or directory\n"));
	if (!getcwd(cwd, sizeof(cwd)))
		return (EXIT_FAILURE);
	if (update_directories(local, cwd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

	// if (access(target_dir, X_OK))
	// 	return (builtin_errors("cd: ", "Permission denied", "\n"));
	// ft_printf("%s\n", target_dir);
	// ft_printf("%d\n", access(target_dir, X_OK));


/*

../path

~/path

cd: name: not a directory

*/