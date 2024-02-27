
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

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
    {
        exit(EXIT_FAILURE);
    }
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
    new->content = copy_environment_variables(environ);
    return (new);
}
