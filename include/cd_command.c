
#include "minishell.h"

int command_cd(char **cmds, t_localenv *local)
{
    const char *home_dir;
    const char *prev_dir;
    char cwd[PATH_MAX];

    (void) local;
    if (cmds[1] == NULL || cmds[1][0] == '\0')
    {
        home_dir = getenv("HOME");
        if (!home_dir)
            return 1;
        if (chdir(home_dir) == -1)
            return 1;
    }
    else if (strcmp(cmds[1], "-") == 0)
    {
        prev_dir = getenv("OLDPWD");
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
    if (setenv("OLDPWD", getenv("PWD"), 1) == -1) // fazer a minha propria setenv
        return 1;
    if (setenv("PWD", cwd, 1) == -1)
        return 1;
    return 0;
}
