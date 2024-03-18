/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_sc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:53:05 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 15:40:35 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_sc(unsigned int nbr, int size, char l)
{
	int	count;

	if (l == 'x')
		count = ft_putnbr_base(nbr, "0123456789abcdef", 1);
	else if (l == 'X')
		count = ft_putnbr_base(nbr, "0123456789ABCDEF", 1);
	return (ft_count_num2(nbr, size));
}
