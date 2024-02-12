
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

char    *master_expander(char *cmd)
{
    char *cmd_var;
    char *curr_env;

    if (!is_valid_to_expand(cmd))
    {
        printf("Warning: '%s' does not exist.\n", cmd);
        return (NULL);
    }
    else if (cmd[0] == '$')
        cmd_var = ft_strdup(cmd + 1);
    else
        return (NULL);
    curr_env = getenv(cmd_var);
    if (curr_env != NULL)
    {
        free(cmd_var);
        return strdup(curr_env);
    }
    else
        printf("Warning: '%s' does not exist.\n", cmd_var);
    return (NULL);
}


//$HOME$home'$HOME'"$HOME""'" = /home/luis-ffe  $HOME /home/luis-ffe'
// $home lowercase disapears is not expanded and not printed
// '$HOME'  in single quotes treated as  literal not expanded
// "$HOME" tretated normally
// "'" prints the





/*to test this make sure you are on the include directory and have done a make for minishell
now just paste this:
cc expansive.c -o expansive -Ilibft -Llibft -lf
./expansive

write comands with $ at the start

make sure the smae functions are comented in the main minishell

*/

int main(void)
{
    char input_cmd[100];
    
    printf("EXPANDER_Minishell/> ");
    fgets(input_cmd, sizeof(input_cmd), stdin);
    input_cmd[strcspn(input_cmd, "\n")] = '\0'; 

    char *expanded_cmd = master_expander(input_cmd);

    if (expanded_cmd != NULL) {
        printf("Expanded command: %s\n", expanded_cmd);
        free(expanded_cmd);
    } else {
        printf("\n");
    }
    return 0;
}