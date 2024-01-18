/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:29:57 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 15:07:51 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ch;

	ch = (char *) str + ft_strlen((char *)str);
	while (*ch != (char) c && ch != str)
	{
		ch--;
	}
	if (*ch == (char) c)
		return (ch);
	else
		return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main () {
   int len;
   const char str[] = "https://www.tutorialspoint.com";
   const char ch = '.';
   char *ret;

   ret = strrchr(str, ch);

   printf("String after |%c| is - |%s|\n", ch, ret);
   
   return(0);
}*/
