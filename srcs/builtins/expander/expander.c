/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:43:32 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/18 10:36:24 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

char	*ds_replace_codeword(char *cmd, char *code, char *env_val)
{
	char	*new;
	char	*start;
	char	*end;
	int		len;

	if (!env_val)
		env_val = "";
	len = ft_strlen(cmd) - ft_strlen(code) + ft_strlen(env_val) + 1;
	new = (char *)malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	start = ft_strnstr(cmd, "$", ft_strlen(cmd)) + 1;
	end = start + ft_strlen(code);
	if (*start == '?')
		end--;
	ft_strlcpy(new, cmd, start - cmd);
	ft_strlcat(new, env_val, len);
	ft_strlcat(new, end, len);
	free(code);
	free(cmd);
	return (new);
}

char	*expand_single_variable(char *cmd, t_localenv *local)
{
	char	*env;
	char	*code_word;
	char	*expanded_str;

	env = NULL;
	code_word = NULL;
	expanded_str = ft_strdup(cmd);
	if (*expanded_str == '\'' && quotes_counter(expanded_str) % 2)
		return (expanded_str);
	while (ft_strnstr(expanded_str, "$", ft_strlen(expanded_str)))
	{
		code_word = get_ds_code(expanded_str);
		if (!code_word || is_str_empty(code_word))
			break ;
		if (!ft_strncmp(code_word, "$?", 2))
		{
			if (env)
				free(env);
			env = ft_itoa(g_signal);
		}
		else
		{
			if (env)
				free(env);
			env = ft_getenv(code_word, local->content);
		}
		expanded_str = ds_replace_codeword(expanded_str, code_word, env);
	}
	if (env)
		free(env);
	return (expanded_str);
}

char	*join_list_contents(t_lstexpand *head)
{
	int			total_length;
	t_lstexpand	*cur;
	char		*joined_content;

	total_length = 0;
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			total_length += ft_strlen(cur->content);
		cur = cur->next;
	}
	joined_content = ft_calloc((total_length + 1), sizeof(char));
	if (!joined_content)
		return (NULL);
	joined_content[0] = '\0';
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			ft_strlcat(joined_content, cur->content, \
				ft_strlen(joined_content) + ft_strlen(cur->content) + 1);
		cur = cur->next;
	}
	return (joined_content);
}

bool	q_lst_clean_helper(t_lstexpand *cur, int len)
{
	if (len >= 2 && ((cur->content[0] == '\'' && \
		cur->content[len - 1] == '\'')))
		return (true);
	else if ((cur->content[0] == '\"' && cur->content[len - 1] == '\"'))
		return (true);
	else
		return (false);
}

void	clean_quotes_in_list(t_lstexpand *head, int len)
{
	t_lstexpand	*cur;
	char		*temp;

	cur = head;
	while (cur != NULL)
	{
		if ((ft_strcmp(cur->content, "''") == 0) || \
			(ft_strcmp(cur->content, "\"\"") == 0))
		{
			free(cur->content);
			cur->content = NULL;
		}
		else
		{
			len = ft_strlen(cur->content);
			if (q_lst_clean_helper(cur, len))
			{
				temp = ft_strdup(cur->content + 1);
				temp[len - 2] = '\0';
				free(cur->content);
				cur->content = temp;
			}
		}
		cur = cur->next;
	}
}
