/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:01:28 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 10:26:11 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Iterates the list ’lst’ and applies the function
’f’ on the content of each node.

Return value: None */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* static void upper(void *content)
{
	char	*c;

	c = (char *)content;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

int	main(void)
{
	t_list *node;

	node = ft_lstnew("NodEUm");
	if (!node)
	{
		printf("memory allocation failed, the new node wasn't created!\n");
		return (1);
	}
	printf("New node was created! node before lstiter: %s\n", (char *)node
		-> content);
	ft_lstiter(node, upper);
	printf("Node after lstiter: %s\n", (char *)node -> content);
	free(node);
	return (0);
} */