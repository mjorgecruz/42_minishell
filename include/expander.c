#include "minishell.h"

char	*get_ds_code(char *cmd)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd)); //encontra $ returna tudo na sua frente
	if (tmp[1] == '?')
		return (ft_strdup("$?")); //se for interrogacao retorna isso
	if (ft_isdigit(tmp[1]))
		return (ft_substr(tmp, 0, 1)); //se for digito not valid RETURN NULL
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_') //enquanto for alphanumerico ou _ is valid!
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
	if (*expanded_str == '\'' && quotes_counter(expanded_str) % 2)               //no caso de haver single quotes em numero impar retorna como esta.
		return (expanded_str);
	while (ft_strnstr(expanded_str, "$", ft_strlen(expanded_str)))
	{
		code_word = get_ds_code(expanded_str);
		if (!code_word || is_str_empty(code_word))
			break ;                                                             //sendo nula ou vazia
		if (!ft_strncmp(code_word, "$?", 2))
			env = "696969";                                                     // codigo de erro???? pid? o que ???
		else
			env = ft_getenv(code_word, local->content);                                            // teremos de substituir isto pela nossa propria versao!  ft_getenv!!!!
		expanded_str = ds_replace_codeword(expanded_str, code_word, env);
	}
	return (expanded_str);
}

char *join_list_contents(t_lstexpand *head)
{
    int total_length;
	t_lstexpand *current;
	char *joined_content;

	total_length = 0;
	current = head;
    while (current != NULL)
    {
        if (current->content != NULL)
            total_length += strlen(current->content);
        current = current->next;
    }
    joined_content = malloc((total_length + 1) * sizeof(char));
    if (!joined_content) return NULL;
    joined_content[0] = '\0';
    current = head;
    while (current != NULL)
    {
        if (current->content != NULL)
            strcat(joined_content, current->content);
        current = current->next;
    }
    return joined_content;
}

void clean_quotes_in_list(t_lstexpand *head)
{
    t_lstexpand *current;
	
	current = head;
    while (current != NULL)
    {
        if ((strcmp(current->content, "''") == 0) || (strcmp(current->content, "\"\"") == 0))
        {
            free(current->content);
            current->content = NULL;
        }
        else
        {
            int len = strlen(current->content);
            if (len >= 2 && ((current->content[0] == '\'' && current->content[len - 1] == '\'') ||
                             (current->content[0] == '\"' && current->content[len - 1] == '\"')))
            {
                char *temp = strdup(current->content + 1);
                temp[len - 2] = '\0';
                free(current->content);
                current->content = temp;
            }
        }
        current = current->next;
    }
}
