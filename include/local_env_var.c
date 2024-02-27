
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
    for (size_t i = 0; i < size; i++)
        *((char *)mem + i) = '\0';
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


int find_variable_index_recursive(const char *variable, char **env, int index)
{
    if (env[index] == NULL)
        return -1;
    if (ft_strncmp(variable, env[index], ft_strlen(variable)) == 0 && env[index][ft_strlen(variable)] == '=')
        return index;
    return find_variable_index_recursive(variable, env, index + 1);
}

int find_variable_index(const char *variable, char **env)
{
    return find_variable_index_recursive(variable, env, 0);
}

int add_variable(const char *variable, char ***env_ptr)
{
    char **env;
    int num_vars;
    char **new_env;
    
    env = *env_ptr;
    num_vars = 0;
    while (env[num_vars] != NULL)
        num_vars++;
    new_env = (char **)ft_memalloc((num_vars + 2) * sizeof(char *));
    if (new_env == NULL)
        return -1;
    env = new_env;
    env[num_vars] = ft_strdup(variable);
    if (env[num_vars] == NULL)
        return -1;
    env[num_vars + 1] = NULL;
    *env_ptr = env;
    printf("ADEDDDDD");
    return 0;
}

int update_variable(const char *variable, char **env)
{
    char *equal_sign;
    int index;

    index = find_variable_index(variable, env);
    if (index != -1)
    {
        equal_sign = ft_strchr(variable, '=');
        *equal_sign = '\0';
        free(&env[index]);
        env[index] = ft_strdup(variable);
        *equal_sign = '=';
        printf("UPDATEDEEEDDDD");
        return 0;
    }
    else
        return add_variable(variable, &env);
}

int command_export(char **cmds, char ***local_env_ptr)
{
    char *variable;
    char *equal_sign;
    char **local_env;
    int result;

    if (cmds == NULL || local_env_ptr == NULL || *local_env_ptr == NULL)
        return -1;
    variable = cmds[1];
    equal_sign = ft_strchr(variable, '=');
    if (equal_sign == NULL || equal_sign == variable)
        return -1;
    local_env = *local_env_ptr;
    if (local_env == NULL)
        return -1;
    result = update_variable(variable, local_env);
    if (result == 0)
    {
        *local_env_ptr = local_env;
        return 0;
    }
    else
        return -1;
}
