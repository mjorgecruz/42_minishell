/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:53:25 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 15:40:32 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_num(int nbr, int size)
{
	long	num;
	int		count;

	num = nbr;
	count = 0;
	if (num < 0)
	{
		num = (-num);
		count++;
	}
	if (num == 0)
		return (1);
	while (num > 0)
	{
		count++;
		num = num / size;
	}
	return (count);
}
