
#include "minishell.h"

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

void *ft_memalloc(size_t size)
{
    void *mem = malloc(size);
    if (mem == NULL)
        return NULL;
    ft_bzero(mem, size);
    return mem;
}

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
