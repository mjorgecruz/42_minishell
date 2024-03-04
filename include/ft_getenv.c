
#include "minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	size_t	len;
	char	**env_var;

	if (name == NULL || envp == NULL)
		return (NULL);
	len = ft_strlen(name);
	env_var = envp;
	while (*env_var)
	{
		if (ft_strncmp(name, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			return (*env_var + len + 1);
		}
		env_var++;
	}
	return (NULL);
}
