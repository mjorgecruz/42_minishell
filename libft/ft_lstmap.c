/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:09:02 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 14:16:50 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*trav;
	t_list	*current;

	if (lst == NULL || !f || !del)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (new_list == NULL)
		return (NULL);
	trav = lst->next;
	current = new_list;
	while (trav != NULL)
	{
		current->next = ft_lstnew(f(trav->content));
		if (current->next == NULL)
		{
			ft_lstclear(&current, del);
			return (NULL);
		}
		trav = trav->next;
		current = current->next;
	}
	return (new_list);
}
