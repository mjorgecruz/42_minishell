
#include "minishell.h"

bool	has_valid_cmd_after(char *str, int pos)
{
	pos = ignore_spaces(str, pos);
	if (is_special_char(str[pos]) || !str[pos])
		return (false);
	else
		return (true);
}

bool check_combs_doubles(char *str, int pos)
{
    if (str[pos] == '>' && str[pos + 1] == '>')
    {
        if (has_valid_cmd_after(str, pos + 2))
            return (true);
        else
            return(error_definer(&str[pos + 2]), false);
    }
    else if (str[pos] == '<' && str[pos + 1] == '<')
    {
        if (has_valid_cmd_after(str, pos + 2))
            return (true);    
    }
    else if (str[pos] == '<' && has_valid_cmd_after(str, pos + 1))
        return (true);
    else if (str[pos] == '>' && str[pos + 1] != '|' && has_valid_cmd_after(str, pos + 1))
        return (true);
    else if (str[pos] == '>' && str[pos + 1] == '|')
    {
        if (has_valid_cmd_after(str, pos + 2))
            return (true);
    }
    return (false);
}

bool    is_invalid_start_sign(char *str)
{
    int i;

    i = 0;
    if (pipe_is_first(str, 0))
    {
        errors(SYNTAX_PIPE, NULL);
        return (true);
    }
    i = ignore_spaces(str, i);
    if (is_special_char(str[i]))
    {
        if (check_combs_doubles(str, i) == false)
            return true;
    }
    return false;
}

bool pipe_is_first(char *s, int pos)
{
	pos = ignore_spaces(s, pos);
	if (s[pos] == '|')
	{
		return (true);
	}
	return (false);
}
