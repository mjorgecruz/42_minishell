#include "minishell.h"

typedef struct s_lstexpand
{
    int id;
    int status;
    char *content;
    struct s_lstexpand *next;
} t_lstexpand;

char	*get_ds_code(char *cmd);
char	*ds_replace_codeword(char *cmd, char *code, char *env_val);
bool	is_str_empty(char *str);
int		quotes_counter(char *cmd);
char	*expand_single_variable(char *cmd);

t_lstexpand *create_node_lstexpand(int status, char *content);
void insert_lstexpand_node(t_lstexpand **head, t_lstexpand *newNode);
void free_lstexpand(t_lstexpand *head);
void print_list(t_lstexpand *head);








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

////////////////////////////// Structure that is used to create a linjed list of the comand by parts to be used by the expander
/*
ex:

$HOME$home'''$HOME'"""$HOME"  balalsksks
[$HOME$home]['']['$HOME'][""]["$HOME"][  balalsksks]             (this is how i want the data to be formated)

has to become: /home/luis-ffe$HOME/home/luis-ffebalalsksks

the linked list divdes them in order by 

[$HOME$home]
['']
['$HOME']
[""]
["$HOME"]
[  balalsksks]

and then need to remove the quotes! and expande the ones that should be expanded
*/

t_lstexpand *create_node_lstexpand(int status, char *content)
{
    t_lstexpand *new_node;
    
    new_node = (t_lstexpand *)malloc(sizeof(t_lstexpand));
    if (!new_node)
        return (NULL);
    new_node->status = status;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

void print_list(t_lstexpand *head)
{
    while (head != NULL)
	{
        printf("Status: %d, Content: %s\n", head->status, head->content);
        head = head->next;
    }
}

void insert_lstexpand_node(t_lstexpand **head, t_lstexpand *newNode)
{
    t_lstexpand *temp;

    if (*head == NULL)
		*head = newNode;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void free_lstexpand(t_lstexpand *head)
{
    t_lstexpand *temp;

    while (head != NULL)
	{
        temp = head;
        head = head->next;
        free(temp->content);
        free(temp);
    }
}

// int main(void)
// {
//     char input_cmd[100];
    
//     printf("EXPANDER_Minishell/> ");
//     fgets(input_cmd, sizeof(input_cmd), stdin);
//     input_cmd[strcspn(input_cmd, "\n")] = '\0'; 
//     char *result = expand_single_variable(input_cmd);
//     printf("Expanded command: %s\n", result);
//     free(result);
//     return 0;
// }

int main()
{
	char *l1 = "Node 1 content";
	char *l2 = "Node 2 content";
	char *l3 = "Node 3 content";

    t_lstexpand *node1 = create_node_lstexpand(1, l1);
    t_lstexpand *node2 = create_node_lstexpand(0, l2);
    t_lstexpand *node3 = create_node_lstexpand(1, l3);
    t_lstexpand *head = NULL;
    insert_lstexpand_node(&head, node1);
    insert_lstexpand_node(&head, node2);
    insert_lstexpand_node(&head, node3);
    printf("Printing the list:\n");
    print_list(head);
    //free_lstexpand(head); //dont free cuz im using string literals only available on the read scope not needed to free
    return 0;
}



////////////////////////////////////// GARBAGE CAN ////////////////////////////////////////////////

/*  functions not in use anymore but work fine and are good!

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

*/
