/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:09:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/15 16:58:50 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

int	change_directory(const char *path)
{
	int	error;

	if (chdir(path) == -1)
	{
		error = errno;
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
	char	*pwd;

	pwd = ft_getenv("PWD", local->content);
	if (ft_setenv("OLDPWD", pwd, local) == -1)
	{
		free(pwd);
		return (-1);
	}
	if (ft_setenv("PWD", cwd, local) == -1)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (EXIT_SUCCESS);
}

char	*space_saver_tilde(char *home_dir, char *dir)
{
	char	*expanded_dir;

	expanded_dir = ft_strjoin(home_dir, dir + 1);
	free(home_dir);
	return (expanded_dir);
}

char	*expand_tilde(char *dir, t_localenv *local)
{
	char	*home_dir;
	char	*expanded_dir;

	if (dir[0] == '~')
	{
		home_dir = get_home_directory(local);
		if (!home_dir)
			return (NULL);
		if (!dir[1])
			return (home_dir);
		if (dir[1] == '/')
		{
			if (dir[2])
				expanded_dir = space_saver_tilde(home_dir, dir);
			else
				return (home_dir);
		}
		else
			expanded_dir = space_saver_tilde(home_dir, dir);
		return (free(home_dir), expanded_dir);
	}
	return (ft_strdup(dir));
}

int	command_cd(char **cmds, t_localenv *local, int err)
{
	char	*target_dir;
	char	cwd[PATH_MAX];

	if (cmds[1] && cmds[2])
		return (builtin_errors("cd: too many arguments", "\n", ""));
	if (cmds[1] == NULL || cmds[1][0] == '\0')
	{
		target_dir = get_home_directory(local);
		if (target_dir == NULL)
			builtin_errors("cd: ", "", ": HOME not set\n");
	}
	else if (ft_strcmp(cmds[1], "-") == 0)
		target_dir = get_previous_directory(local);
	else
		target_dir = expand_tilde(cmds[1], local);
	if (!target_dir)
		return (EXIT_FAILURE);
	err = change_directory(target_dir);
	if (err == 13)
		return (free(target_dir), builtin_errors("cd: ", "", ": Permission denied\n"));
	if (err == 2)
		return (free(target_dir), builtin_errors("cd: ", cmds[1], ": no such file or directory\n"));
	if (!getcwd(cwd, sizeof(cwd)))
		return (free(target_dir), EXIT_FAILURE);
	if (update_directories(local, cwd) == -1)
		return (free(target_dir), EXIT_FAILURE);
	if (cmds[1] && cmds[1][0] != '\0' && cmds[1][0] != '~')
		free(target_dir);
	else if (target_dir)
		free(target_dir);
	return (EXIT_SUCCESS);
}
