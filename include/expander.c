
#include "minishell.h"

bool is_valid_to_expand(const char *var)
{
    int i;

    i = 0;
    if (var[0] != '$')
        return (false);
    else if (ft_isdigit(var[1]))
        return (false);
    while (var[++i])
    {
        if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
            return(false);
    }
    return (true);
}

/*cmd has to reach here with just $ at the start and not any other $*/
char    *master_expander(char *cmd)
{
    char *cmd_var;
    char *curr_env;

    if (!is_valid_to_expand(cmd))
    {
        printf("Warning: Environment variable '%s' does not exist.\n", cmd);
        return (NULL);
    }
    else if (cmd[0] == '$')
        cmd_var = ft_strdup(cmd + 1);
    else
        return (NULL);
    curr_env = getenv(cmd_var);
    free(cmd_var);
    if (curr_env != NULL)
        return strdup(curr_env);
    else
        printf("Warning: Environment variable '%s' does not exist.\n", cmd_var);
    return (NULL);
}

/*

TO DO


$HOME$HOME has to print twice without spaces


make sure it reaches here without "" nor '' 
and that parser also should divide the  $HOME$HOME
or flag the '' invalid quotes for no expansion at all



*/

/* 
bool is_valid_to_expand(const char *var);

already detects if it has more than 1 $

after a $ there are only 3 allowed chars... 
alphabetics underscores and NUmerics but not numerics right  after the $
$   not valid
$$ not
$1  not
$A_ valid
$_1a valid
$a_1 valid
$_a1dswda12e1_adq3 valid
*/
