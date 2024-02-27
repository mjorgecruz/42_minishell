
#include "minishell.h"

char *ft_strncpy(char *dst, const char *src, size_t n)
{
    char *start = dst;
    while (n > 0 && *src != '\0')
    {
        *dst++ = *src++;
        n--;
    }
    while (n > 0)
    {
        *dst++ = '\0';
        n--;
    }
    return start;
}

void *ft_memalloc(size_t size)
{
    void *mem = malloc(size);
    if (mem == NULL)
        return NULL;
    ft_bzero(mem, size);
    return mem;
}

char **copy_env_var_utils(char **env, int num_vars, char **env_copy)
{
    int len;

    if (*env == NULL)
    {
        env_copy[num_vars] = NULL;
        return env_copy;
    }
    len = ft_strlen(*env) + 1;
    env_copy[num_vars] = (char *)malloc(len * sizeof(char));
    if (env_copy[num_vars] == NULL)
    {
        exit(EXIT_FAILURE);
    }
    ft_strncpy(env_copy[num_vars], *env, len);
    return (copy_env_var_utils(env + 1, num_vars + 1, env_copy));
}

char **copy_environment_variables(char **environ)
{
    int num_vars;
    char **env;
    char **env_copy;

    num_vars = 0;
    env = environ;
    while (*env != NULL)
    {
        num_vars++;
        env++;
    }
    env_copy = (char **)malloc((num_vars + 1) * sizeof(char *));
    if (env_copy == NULL)
        exit(EXIT_FAILURE);
    return (copy_env_var_utils(environ, 0, env_copy));
}

t_localenv *env_init(char **envirion)
{
    t_localenv *new;

    new = malloc(sizeof(t_localenv));
    if (new == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new->content = copy_environment_variables(envirion);
    return (new);
}

char *extract_variable_name(const char *variable)
{
    int len;
    char *name;
    char *equal_sign;
    
    len = 0;
    equal_sign = ft_strchr(variable, '=');
    if (equal_sign != NULL)
    {
        while (variable[len] != '=' && variable[len] != '\0')
            len++;
    }
    else
    {
        while (variable[len] != '\0')
            len++;
    }
    name = (char *)ft_memalloc(len + 1);
    if (!name)
        return NULL;
    len = -1;
    while (variable[++len] != '=' && variable[len] != '\0')
    {
        name[len] = variable[len];
    }
    return name;
}

int find_variable_index_recursive(const char *name, char **env, int index)
{
    if (env[index] == NULL)
        return -1;
    if (ft_strncmp(name, env[index], ft_strlen(name)) == 0 && env[index][ft_strlen(name)] == '=')
    {
        return index;
    }
    return find_variable_index_recursive(name, env, index + 1);
}

int find_variable_index(const char *variable, char **env)
{
    char *name;
    int ret;

    name = extract_variable_name(variable);
    ret = find_variable_index_recursive(name, env, 0);
    free(name);
    return ret;
}
void ft_free_str_array(char **ar_str)
{
    int i;

    if (!ar_str)
        return;
    i = 0;
    while (ar_str[i])
    {
        free(&ar_str[i]);
        i++;
    }
    free(ar_str);
}




// necvessario dividir esta function em mais 

int add_variable(const char *variable, t_localenv *local)
{
    int num_vars;
    char **new_env;
    int i;

    if (!local)
        return -1;
    num_vars = 0;
    while (local->content[num_vars] != NULL)
        num_vars++;
    new_env = (char **)ft_memalloc((num_vars + 2) * sizeof(char *));
    if (!new_env)
        return -1;
    i = 0;
    while (i < num_vars)
    {
        new_env[i] = ft_strdup(local->content[i]);
        if (!new_env[i])
        {
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return -1;
        }
        i++;
    }
    new_env[i] = ft_strdup(variable);
    if (!new_env[i])
    {
        while (i > 0)
            free(new_env[--i]);
        free(new_env);
        return -1;
    }
    new_env[num_vars + 1] = NULL;
    i = -1;
    while (local->content[++i])
        free(local->content[i]);
    local->content = new_env;
    return 0;
}


int update_variable(const char *variable, t_localenv *local)
{
    char *equal_sign;
    char *variable_copy;
    int index;

    if (!local || !local->content)
        return -1;
    index = find_variable_index(variable, local->content);
    if (index != -1)
    {
        variable_copy = ft_strdup(variable);
        if (!variable_copy)
            return -1;
        equal_sign = ft_strchr(variable_copy, '=');
        if (!equal_sign)
        {
            free(variable_copy);
            return -1;
        }
        free(local->content[index]);
        local->content[index] = variable_copy;
        return 0;
    }
    else
        return (add_variable(variable, local));
}

int command_export(char **cmds, t_localenv *local)
{
    char *variable;
    char *equal_sign;
    int i = -1;

    if (cmds == NULL || local == NULL || local->content == NULL)
        return -1;
    if (cmds[1] == NULL)
    {
        printf("Usage: export VARIABLE=VALUE\n");
        return -1;
    }
    variable = cmds[1];
    equal_sign = ft_strchr(variable, '=');
    if (equal_sign == NULL || equal_sign == variable)
        return -1;
    if (update_variable(variable, local) == 0)
    {
        while (local->content[++i])
            printf("\n [%i] LIST: %s", i, local->content[i]);        //testes da lista apagar
        return 0;
    }
    else
        return -1;
}
