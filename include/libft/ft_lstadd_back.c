/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 22:01:58 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 10:28:59 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*trav;
	t_list	*prev;

	trav = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (trav != NULL)
	{
		prev = trav;
		trav = trav->next;
	}
	prev->next = new;
}
