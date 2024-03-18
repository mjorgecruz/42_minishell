/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:22 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 11:44:58 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t				i;
	unsigned const char	*ch1;
	unsigned const char	*ch2;

	ch1 = str1;
	ch2 = str2;
	i = 0;
	if (n == 0)
		return (0);
	while (*(ch1 + i) == *(ch2 + i) && i < n - 1)
		i++;
	return (*(ch1 + i) - *(ch2 + i));
}
/*
#include <stdio.h>
#include <string.h>

int main () {
	char str1[15];
	char str2[15];
	int ret;

	memcpy(str1, "abcdef", 6);
	memcpy(str2, "ABCDEF", 6);

	ret = ft_memcmp(str1, str2, 5);

	if(ret > 0) {
		printf("str2 is less than str1");
	} else if(ret < 0) {
		printf("str1 is less than str2");
	} else {
		printf("str1 is equal to str2");
	}

	return(0);
}*/
