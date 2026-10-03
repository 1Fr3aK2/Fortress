/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:13:40 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:12:43 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Adds the node ’new’ at the beginning of the list.

Return: value None */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* int main()
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("node1");
	t_list *node2 = ft_lstnew("node2");
	t_list *node3 = ft_lstnew("node3");

	if (!node1 || !node2 || !node3)
	{
		printf("Memory allocation failed!\n");
		return (1);
	}
	ft_lstadd_front(&lst, node1);
	ft_lstadd_front(&lst, node2);
	ft_lstadd_front(&lst, node3);

	printf("List after adition of nodes:\n");
	while(lst)
	{
		printf("%s\n", (char *)lst -> content);
		lst = lst ->next;
	}
	free(node1);
	free(node2);
	free(node3);
	free(lst);
	return(0);
} */