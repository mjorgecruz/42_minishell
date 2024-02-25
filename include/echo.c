
#include "minishell.h"
#include "builtins.h"


/*deals with the newline -n -n -nnnnnnn etc*/
bool    ft_find_n(char *str)
{
    int i;

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

/*expander needs to be integrated for the comand string list */

int	command_echo(char **cmds)
{
    int i;
	bool n_flag;
	
	i = 0;
	n_flag = false;
    while (cmds[++i] && ft_find_n(cmds[i]))
        n_flag = true;
    while (cmds[i] != NULL)
    {
        printf("%s ", cmds[i]);
        i++;
    }
    if (!n_flag)
		printf("\n");
	return (i);
}
