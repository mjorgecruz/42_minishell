
#include "minishell.h"

bool	ft_find_n(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (false);
	if (str[i] && str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (false);
		}
		return (true);
	}
	return (false);
}

// e se o expandido tive -n??
int	command_echo(char **cmds, t_localenv *local)
{
	int		i;
	bool	n_flag;
	char	*exp_temp;

	i = 0;
	n_flag = false;
	while (cmds[++i] && ft_find_n(cmds[i]))
		n_flag = true;
	while (cmds[i] != NULL)
	{
		exp_temp = master_expander(cmds[i], local);
		if (exp_temp)
		{
			printf("%s ", exp_temp);
			free(exp_temp);
		}
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (i);
}
