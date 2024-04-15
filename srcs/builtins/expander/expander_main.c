/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:25 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/15 14:53:11 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

static char	*check_for_tilde(char *str, t_localenv *local);

char	*master_expander(char *cmd, t_localenv *local)
{
	t_lstexpand	*in_cmd_list;
	char		*joined_content;

	in_cmd_list = NULL;
	create_list_quotes(cmd, &in_cmd_list);
	expand_content_in_list(in_cmd_list, local);
	clean_quotes_in_list(in_cmd_list, 0);
	joined_content = join_list_contents(in_cmd_list);
	free_lstexpand(in_cmd_list);
	in_cmd_list = NULL;
	return (joined_content);
}

char	*master_expander_out(char *cmd, t_localenv *local)
{
	t_lstexpand	*in_cmd_list;
	char		*joined_content;

	in_cmd_list = NULL;
	create_list_quotes(cmd, &in_cmd_list);
	expand_content_in_list(in_cmd_list, local);
	clean_quotes_in_list(in_cmd_list, 0);
	joined_content = join_list_contents(in_cmd_list);
	joined_content = check_for_tilde(joined_content, local);
	free_lstexpand(in_cmd_list);
	in_cmd_list = NULL;
	return (joined_content);
}

char	*expander_heredocs(char *cmd, t_localenv *local)
{
	t_lstexpand	*in_cmd_list;
	char		*joined_content;

	in_cmd_list = NULL;
	create_list_quotes(cmd, &in_cmd_list);
	expand_content_in_list(in_cmd_list, local);
	joined_content = join_list_contents(in_cmd_list);
	free_lstexpand(in_cmd_list);
	in_cmd_list = NULL;
	free(cmd);
	return (joined_content);
}

static char	*check_for_tilde(char *str,  t_localenv *local)
{
	char	*home_dir;
	int		i;
	char	*new_str;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '~')
		i++;
	if (str[i] == '~')
	{
		home_dir = get_home_directory(local);
		if (home_dir == NULL)
			return(str);
		new_str = ft_calloc(ft_strlen(str) + ft_strlen(home_dir) + 1, sizeof(char));
		i = 0;
		while(str[i])
		{
			if (str[i] == '~')
			{
				i++;
				k = 0;
				while (home_dir[k])
				{
					new_str[j] = home_dir[k];
					j++;
					k++;
				}
			}
			else
			{
				new_str[j] = str[i];
				j++;
				i++;
			}
			if (str[i])
				i++;
		}
		return(free(str), free(home_dir), new_str);
	}
	else
		return(str);
}
