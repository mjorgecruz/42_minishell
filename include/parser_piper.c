
#include "minishell.h"

bool	has_valid_cmd_after(char *str, int pos)
{
	if (!str[pos])
		return (false);
	pos = ignore_spaces(str, pos);
	if (!str[pos] || is_special_char(str[pos]))
		return (false);
	else
		return (true);
}

bool check_combs_doubles(char *str, int pos)
{
	if (str[pos] == '>' && str[pos + 1] == '>')
		return (check_combs_doubles_rr_rr(str, pos));
	else if (str[pos] == '<' && str[pos + 1] == '<')
		return (check_combs_doubles_lr_lr(str, pos));
	else if((str[pos] == '<' || str[pos] == '>') && str[pos + 1] == '&')
		return(errors(SYNTAX_AMP, NULL), false);
	else if (str[pos] == '>' && str[pos + 1] == '|')
	{
		if (has_valid_cmd_after(str, pos + 2))
			return (true);
		return(errors(SYNTAX_NEWLINE, NULL), false);
	}
	else if (str[pos] == '<' && str[pos + 1] == '|')
		return(errors(SYNTAX_PIPE, NULL), false);
	else if ((str[pos] == '<' || str[pos] == '>') && has_valid_cmd_after(str, pos + 1))
		return (true);
	check_next_cmd(&str[pos + 1]);
	return (true);
}

bool check_combs_doubles_rr_rr(char *str, int pos)
{
	if (has_valid_cmd_after(str, pos + 2))
		return (true);
	return(error_definer(&str[pos + 2]), false);
}

bool check_combs_doubles_lr_lr(char *str, int pos)
{
	if (has_valid_cmd_after(str, pos + 2))
		return (true);
	check_next_cmd(&str[pos + 1]);
	return(error_definer(&str[pos + 2]), false);
}

bool    is_invalid_start_sign(char *str)
{
	int i;
	char c;

	i = 0;
	c = 0;
	i = ignore_spaces(str, i);
	if (pipe_is_first(str, i))
		return(start_sign_pipe(str, i));
	i = ignore_spaces(str, i);
	if (is_special_char(str[i]))
	{
		c = str[i];
		i = ignore_spaces(str, i + 1);
		if (str[i] == '\0')
		{
			if (c == '&')
				return (errors(SYNTAX_AMP, NULL), true);
			return (errors(SYNTAX_NEWLINE, NULL), true);
		}
		else if (check_combs_doubles(str, i - 1) == false)
			return (true);
	}
	return (false);
}

bool    start_sign_pipe(char *str, int i)
{
	if (str[i] == str[i + 1]) 
		error_definer(&str[i]);
	else
		errors(SYNTAX_PIPE, NULL);
	return (true);
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

void	check_next_cmd(char *str)
{
	int		pos;

	pos = 0;
	pos = ignore_spaces(str, pos);
	if (str[pos] == '\0')
		errors(SYNTAX_NEWLINE, NULL);
}
