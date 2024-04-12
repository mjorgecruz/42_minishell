/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:25 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/12 09:30:45 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

char	*master_expander(char *cmd, t_localenv *local)
{
	t_lstexpand	*in_cmd_list;
	char		*joined_content;
	(void)		local;

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