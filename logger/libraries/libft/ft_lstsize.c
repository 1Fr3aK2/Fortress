/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:50 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:16:24 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Counts the number of nodes in a list.

Return value: The length of the list */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

/* int main()
{
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *list = NULL;
	int size;

	node1 = ft_lstnew("hello, world!");
	node2 = ft_lstnew("hello, world!");
	node3 = ft_lstnew("hello, world!");

	list = node1;
	node1 -> next = node2;
	node2 -> next = node3;
	node3 -> next = NULL;
	if (!node1 || !node2 || !node3)
	{
		printf("Memory allocation failed, the new nodes weren't crated\n");
		return(1);
	}
	size = ft_lstsize(list);
	printf("The new node was created with success, the content of the new node:
		%s\n", (char *)list -> content);
	printf("the size of the new lst is: %d\n", size);
	free(list);
	return (0);
} */