/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:54:50 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:05:56 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*trav;
	t_list	*prev;

	trav = lst;
	prev = trav;
	while (trav != NULL)
	{
		prev = trav;
		trav = trav->next;
	}
	return (prev);
}
