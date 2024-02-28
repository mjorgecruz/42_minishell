
#include "minishell.h"

size_t	ft_strarrlen(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char	**ft_strarrdup(char **src)
{
	size_t	len;
	char	**dst;
	size_t	i;

	if (!src)
		return (NULL);
	len = ft_strarrlen(src);
	dst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_free_str_array(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}


void print_next_string(char **str)
{
    while (*str != NULL)
	{
        printf("%s\n", *str);
        str++;
    }
}

void swap_strings(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}
