/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:17 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/17 14:31:52 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	old_size;

	if (!ptr)
		return (ft_memalloc(size));
	old_size = ft_strlen(ptr) + 1;
	if (size <= old_size)
		return (ptr);
	new_ptr = ft_memalloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
