
#include "minishell.h"





typedef struct s_expstr
{
	char		*str;
    int         i;

}	t_expstr;

t_expstr *init_expstr(char *cmd_str)
{
    t_expstr *str_data = malloc(sizeof(t_expstr));
    if (!str_data)
        return (NULL);
    str_data->i = 0;
    str_data->str = ft_strcpy(cmd_str);
    return (str_data);
}

char *shell_like_expander(char *cmd_str)
{
    t_expstr *str_data;
    char *expanded_str;

    str_data = init_expstr(cmd_str);

    /*function to iterate and expand the str in the structure*/

    expanded_str = ft_strcpy(str_data->str);
    free (str_data);
    return (expanded_str);
}







/*supposed to build the entire new string with the env var expanded*/

// char *expand_into_new_str(char *str)
// {
//     bool s_quote;
//     bool d_quote;
//     int i;

//     s_quote = false;
//     d_quote = false;
//     i = -1;
//     while (str[++i])
//     {
//         if (!d_quote && !s_quote && str[i] == "\"" )
//             d_quote = true;
//         else if (d_quote && str[i] == "\"" )
//             d_quote = false;
//         else if (!d_quote && !s_quote && str[i] == "\'" )
//             s_quote = true;
//         else if (s_quote && str[i] == "\'" )
//             s_quote = false;
//     }
// }


/*
expandir ou nao quote management
"" expande
single not


is_valid_to_expand e expande or else fica igual(aspens removal in the endens)

expande- copiar tudo o que ta antes e depois para compor a frase *placeholders

master_expander(substitui o que esta no $)

colar tudo 

remove aspens if needed

ft_strdup
ft_strlcat
*/

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

/* expands the given string that must start with the $ and returns already cleared of $
*/
char    *substr_expander(char *cmd)
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



int main(void)
{
    char input_cmd[100];
    
    printf("EXPANDER_Minishell/> ");
    fgets(input_cmd, sizeof(input_cmd), stdin);
    input_cmd[strcspn(input_cmd, "\n")] = '\0'; 

    char *expanded_cmd = substr_expander(input_cmd);

    if (expanded_cmd != NULL) {
        printf("Expanded command: %s\n", expanded_cmd);
        free(expanded_cmd);
    } else {
        printf("\n");
    }
    return 0;
}

//$HOME$home'$HOME'"$HOME""'" = /home/luis-ffe  $HOME /home/luis-ffe'
// $home lowercase disapears is not expanded and not printed
// '$HOME'   in single quotes treated as  literal not expanded
// "$HOME"   tretated normally
// "'" prints the

/*to test this make sure you are on the include directory and have done a make for minishell
now just paste this:
cc expansive.c -o expansive -Ilibft -Llibft -lf
./expansive

write comands with $ at the start

make sure the smae functions are comented in the main minishell

*/
