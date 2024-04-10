/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:44 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/10 14:06:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_ds_code(char *cmd)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit(tmp[1]))
		return (ft_substr(tmp, 0, 1));
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	return (ft_substr(tmp, 1, len));
}

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

	expanded_str = ft_strdup(cmd);
	if (*expanded_str == '\'' && quotes_counter(expanded_str) % 2)
		return (expanded_str);
	while (ft_strnstr(expanded_str, "$", ft_strlen(expanded_str)))
	{
		code_word = get_ds_code(expanded_str);
		if (!code_word || is_str_empty(code_word))
			break ;
		if (!ft_strncmp(code_word, "$?", 2))
			env = ft_itoa(g_signal);
		else
			env = ft_getenv(code_word, local->content);
		expanded_str = ds_replace_codeword(expanded_str, code_word, env);
	}
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
			strcat(joined_content, cur->content);
		cur = cur->next;
	}
	return (joined_content);
}

void	clean_quotes_in_list(t_lstexpand *head, int len)
{
	t_lstexpand	*cur;
	char		*temp;

	cur = head;
	while (cur != NULL)
	{
		if ((ft_strcmp(cur->content, "''") == 0) || (ft_strcmp(cur->content, "\"\"") == 0))
		{
			free(cur->content);
			cur->content = NULL;
		}
		else
		{
			len = ft_strlen(cur->content);
			if (len >= 2 && ((cur->content[0] == '\'' && cur->content[len - 1] == '\'') || (cur->content[0] == '\"' && cur->content[len - 1] == '\"')))
			{
				temp = strdup(cur->content + 1);
				temp[len - 2] = '\0';
				free(cur->content);
				cur->content = temp;
			}
		}
		cur = cur->next;
	}
}
