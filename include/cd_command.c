
#include "minishell.h"

int add_env_variable(const char *name, const char *value, t_localenv *local)
{
    char **new_content;
    char *new_var;
    char *temp;

    size_t index = 0;
    while (local->content[index] != NULL)
        index++;
    new_content = realloc(local->content, (index + 2) * sizeof(char *)); //posso usar realloc?
    if (new_content == NULL)
        return -1;
    local->content = new_content;
    new_var = ft_strjoin(name, "=");
    if (new_var == NULL)
        return -1;
    temp = new_var;
    new_var = ft_strjoin(new_var, value);
    free(temp);
    if (new_var == NULL)
        return -1;
    local->content[index] = new_var;
    local->content[index + 1] = NULL;
    return 0;
}

int update_env_variable(const char *name, const char *value, t_localenv *local)
{
    size_t index;
    char *new_var;
    char *temp;

    index = 0;
    while (local->content[index] != NULL)
    {
        if (ft_strncmp(local->content[index], name, ft_strlen(name)) == 0 && local->content[index][ft_strlen(name)] == '=')
        {
            free(local->content[index]);
            new_var = ft_strjoin(name, "=");
            if (new_var == NULL)
                return -1;
            temp = new_var;
            new_var = ft_strjoin(new_var, value);
            free(temp);
            if (new_var == NULL)
                return -1;
            local->content[index] = new_var;
            return 0;
        }
        index++;
    }
    return -1;
}

int ft_setenv(const char *name, const char *value, t_localenv *local)
{
    if (local == NULL || name == NULL)
        return -1;
    if (update_env_variable(name, value, local) == -1)
    {
        if (add_env_variable(name, value, local) == -1)
            return -1;
    }
    return 0;
}

int command_cd(char **cmds, t_localenv *local)
{
    const char *home_dir;
    const char *prev_dir;
    char cwd[PATH_MAX];

    if (cmds[1] == NULL || cmds[1][0] == '\0')
    {
        home_dir = ft_getenv("HOME", local->content);
        if (!home_dir)
            return 1;
        if (chdir(home_dir) == -1)
            return 1;
    }
    else if (strcmp(cmds[1], "-") == 0)
    {
        prev_dir = ft_getenv("OLDPWD", local->content);
        if (!prev_dir)
            return 1;
        if (chdir(prev_dir) == -1)
            return 1;
    }
    else
        if (chdir(cmds[1]) == -1)
            return 1;
    if (!getcwd(cwd, sizeof(cwd)))
        return 1;
    if (ft_setenv("OLDPWD", ft_getenv("PWD", local->content), local) == -1)
        return 1;
    if (ft_setenv("PWD", cwd, local) == -1)
        return 1;
    return 0;
}

// int command_cd(char **cmds, t_localenv *local)
// {
//     const char *home_dir;
//     const char *prev_dir;
//     char cwd[PATH_MAX];

//     (void) local;
//     if (cmds[1] == NULL || cmds[1][0] == '\0')
//     {
//         home_dir = getenv("HOME");
//         if (!home_dir)
//             return 1;
//         if (chdir(home_dir) == -1)
//             return 1;
//     }
//     else if (strcmp(cmds[1], "-") == 0)
//     {
//         prev_dir = getenv("OLDPWD");
//         if (!prev_dir)
//             return 1;
//         if (chdir(prev_dir) == -1)
//             return 1;
//     }
//     else
//         if (chdir(cmds[1]) == -1)
//             return 1;
//     if (!getcwd(cwd, sizeof(cwd)))
//         return 1;
//     if (setenv("OLDPWD", getenv("PWD"), 1) == -1)
//         return 1;
//     if (setenv("PWD", cwd, 1) == -1)
//         return 1;
//     return 0;
// }
