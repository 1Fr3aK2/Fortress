/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:16:22 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:15:36 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.*/

/*Return value : The new list.
NULL if the allocation fails.*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*node;
	void	*content;

	newlst = NULL;
	node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, node);
		lst = lst->next;
	}
	return (newlst);
}

/* static void del(void *content)
{
	free(content);
}

static void	*upper(void *content)
{
	char	*c;

	c = (char *)content;
	while (*c != '\0')
	{
		if (*c >= 'a' && *c <= 'z')
			*c -= 32; // Subtrai 32 para converter para maiúscula
		c++;
	}
	return (content);
}

int	main(void)
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("A faZEr A mAiN dIA VINTE e um\n");

	lst = node1;
	if(!node1)
	{
		printf("Memory allocation failed, the node wasn't created\n");
		return (1);
	}
	printf("The node was created and its content before lstmap is: %s\n",
		lst->content);
	lst = ft_lstmap(lst, &upper, &del); // Remova o & antes de lst
	printf("The content of the list after lstmap is: %s\n", lst->content);
		// Adicione uma vírgula aqui
	free(lst); // Liberar a lista após seu uso
	return (0);
} */