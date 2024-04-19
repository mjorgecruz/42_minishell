/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:56:44 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 08:00:00 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_ds_code(char *cmd)
{
	char	*tmp;
	int		len;
	char	*end;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd));
	if (!(*(tmp + 1)) || is_space(*(tmp + 1)) || \
		*(tmp + 1) == '\"' || *(tmp + 1) == '\'')
		return (NULL);
	if (tmp[1] == '?')
	{
		end = ft_strdup("$?");
		return (end);
	}
	if (ft_isdigit(tmp[1]))
	{
		return (ft_substr(tmp, 0, 1));
	}
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	end = ft_substr(tmp, 1, len);
	return (end);
}

char	*ft_env_itoa(char *env)
{
	if (env)
		free(env);
	env = ft_itoa(g_signal);
	return (env);
}

char	*ft_env_getenv(char *env, char *code_w, t_localenv *local)
{
	if (env)
		free(env);
	env = ft_getenv(code_w, local->content);
	return (env);
}
