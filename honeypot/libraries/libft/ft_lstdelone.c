/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:14:48 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:13:51 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed.

Return value: None */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

/* static void del(void *content)
{
	free(content);
}
int	main(void)
{
	t_list *node1;

	node1 = ft_lstnew("Node1");
	if(!node1)
	{
		printf("Memory allocation failed, the node wasn't created!\n");
		return (1);
	}
	printf("The node was created,
		the content of the node before of lstdelone is: %s\n", node1
		-> content);
	ft_lstdelone(node1, del);
	printf("The content and the node were deleted");

	return(0);
} */