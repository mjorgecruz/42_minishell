/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:07:10 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:05:02 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*trav;

	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		trav = current->next;
		free(current);
		current = trav;
	}
	*lst = NULL;
}
