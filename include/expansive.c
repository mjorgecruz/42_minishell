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

bool is_str_empty(char *str)
{
	if (!str)
		return (true);
	if (*str == '\0' || *str == '\n' || *str == '\t')
		return (true);
	return (false);
}

int	quotes_counter(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = cmd[i];
	while (cmd[i] && cmd[i] == quote)
		i++;
	return (i);
}

/*

necessita receber o comando dividido
'$HOME'"$HOME"$HOME
tenho de separa o que esta dentro de singles do restante e depois tenho de remover
as aspas

*/

char	*expand_single_variable(char *cmd)
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
			env = getenv(code_word);                                            // teremos de substituir isto pela nossa propria versao!  ft_getenv!!!!
		expanded_str = ds_replace_codeword(expanded_str, code_word, env);
	}
	return (expanded_str);
}


typedef struct s_lstexpand {
    int id;
    int status;
    char *content;
    struct s_lstexpand *next;
} t_lstexpand;

t_lstexpand *create_node_lstexpand(int id, int status, char *content)
{
    t_lstexpand *new_node;
    
    new_node = (t_lstexpand *)malloc(sizeof(t_lstexpand));
    if (!new_node)
        return (NULL);
    new_node->id = id;
    new_node->status = status;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}
















int main(void)
{
    char input_cmd[100];
    
    printf("EXPANDER_Minishell/> ");
    fgets(input_cmd, sizeof(input_cmd), stdin);
    input_cmd[strcspn(input_cmd, "\n")] = '\0'; 
    char *result = expand_single_variable(input_cmd);
    printf("Expanded command: %s\n", result);
    free(result);
    return 0;
}

// typedef struct s_expstr
// {
// 	char		*str;
//     int         i;

// }	t_expstr;

// t_expstr *init_expstr(char *cmd_str)
// {
//     t_expstr *str_data = malloc(sizeof(t_expstr));
//     if (!str_data)
//         return (NULL);
//     str_data->i = 0;
//     str_data->str = ft_strcpy(cmd_str);
//     return (str_data);
// }

// char *shell_like_expander(char *cmd_str)
// {
//     t_expstr *str_data;
//     char *expanded_str;

//     str_data = init_expstr(cmd_str);

//     /*function to iterate and expand the str in the structure*/

//     expanded_str = ft_strcpy(str_data->str);
//     free (str_data);
//     return (expanded_str);
// }

// /*supposed to build the entire new string with the env var expanded*/

// // char *expand_into_new_str(char *str)
// // {
// //     bool s_quote;
// //     bool d_quote;
// //     int i;

// //     s_quote = false;
// //     d_quote = false;
// //     i = -1;
// //     while (str[++i])
// //     {
// //         if (!d_quote && !s_quote && str[i] == "\"" )
// //             d_quote = true;
// //         else if (d_quote && str[i] == "\"" )
// //             d_quote = false;
// //         else if (!d_quote && !s_quote && str[i] == "\'" )
// //             s_quote = true;
// //         else if (s_quote && str[i] == "\'" )
// //             s_quote = false;
// //     }
// // }


// /*
// expandir ou nao quote management
// "" expande
// single not


// is_valid_to_expand e expande or else fica igual(aspens removal in the endens)

// expande- copiar tudo o que ta antes e depois para compor a frase *placeholders

// master_expander(substitui o que esta no $)

// colar tudo 

// remove aspens if needed

// ft_strdup
// ft_strlcat
// */

// bool is_valid_to_expand(const char *var)
// {
//     int i;

//     i = 0;
//     if (var[0] != '$')
//         return (false);
//     else if (ft_isdigit(var[1]))
//         return (false);
//     while (var[++i])
//     {
//         if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
//             return(false);
//     }
//     return (true);
// }

// /* expands the given string that must start with the $ and returns already cleared of $
// */
// char    *substr_expander(char *cmd)
// {
//     char *cmd_var;
//     char *curr_env;

//     if (!is_valid_to_expand(cmd))
//     {
//         printf("Warning: '%s' does not exist.\n", cmd);
//         return (NULL);
//     }
//     else if (cmd[0] == '$')
//         cmd_var = ft_strdup(cmd + 1);
//     else
//         return (NULL);
//     curr_env = getenv(cmd_var);
//     if (curr_env != NULL)
//     {
//         free(cmd_var);
//         return strdup(curr_env);
//     }
//     else
//         printf("Warning: '%s' does not exist.\n", cmd_var);
//     return (NULL);
// }

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


// int main(void)
// {
//     char input_cmd[100];
    
//     printf("EXPANDER_Minishell/> ");
//     fgets(input_cmd, sizeof(input_cmd), stdin);
//     input_cmd[strcspn(input_cmd, "\n")] = '\0'; 
//     char *result = get_ds_code(input_cmd);
//     printf("Expanded command: %s\n", result);
//     return 0;
// }
