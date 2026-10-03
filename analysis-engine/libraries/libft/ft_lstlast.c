/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:46:14 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:14:25 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Returns the last node of the list.

Return value: Last node of the list */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/* int main()
{
	t_list *node1 =  ft_lstnew("Node1");
	t_list	*node2 = ft_lstnew("Node2");
	t_list *node3 = ft_lstnew("Node3");


	node1 -> next = node2;
	node2 -> next = node3;

	t_list *last =  ft_lstlast(node1);
	if(!node1 || !node2 || !node3)
	{
		printf("Memory allocation failed and the nodes weren't created!\n");
		return (1);
	}
	printf("New nodes were created with success!\n");
	printf("the last node of the list is: %s\n", (char *)last->content);
	free(node1);
	free(node2);
	free(node3);
	return(0);
} */
