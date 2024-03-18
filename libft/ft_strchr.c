/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:22:34 by masoares          #+#    #+#             */
/*   Updated: 2023/10/05 19:25:34 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

char	*ft_strchr(const char *str, int c)
{
	char	*ch;
	int		i;

	i = 0;
	ch = (char *) str;
	while (*ch != (char) c && *ch != '\0')
	{
		ch++;
	}
	if (*ch == (char) c)
		return (ch);
	else
		return (NULL);
}
