/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:31:45 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:16:12 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.

Return value: The new node */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/* int main()
{
	t_list *newnode;

	newnode = ft_lstnew("hello, world!");
	if (newnode)
	{
		printf("Newnode created with success, content of the node: %s\n",
			(char *)newnode -> content);
		free(newnode);
	}
	else
	{
		printf("Memory allocation failed, node wasn't created\n");
		return (1);
	}
	free(newnode);
	return (0);
} */