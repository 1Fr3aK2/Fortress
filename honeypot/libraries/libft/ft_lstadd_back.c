/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:02:04 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 11:55:20 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Adds the node ’new’ at the end of the list.

Return value: None */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
/* int main()
{
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew("Node1");
	t_list *node2 = ft_lstnew("Node2");
	t_list *node3 = ft_lstnew("Node3");

	if(!node1 || !node2 || !node3)
	{
		printf("Memory allocation failed!\n");
		return(1);
	}
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstadd_back(&lst, node3);

	printf("List ater adition of nodes: \n");
	while (lst != NULL)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	free(node1);
	free(node2);
	free(node3);
	free(lst);
	return (0);
} */

/* a primeira verificação verifica se o
ponteiro para o ponteiro lst é nulo. Se for nulo, significa
que não há lista para adicionar um novo elemento ao final,
então a função retorna sem fazer nada.
Essa verificação protege contra o caso em que a lista não
foi inicializada ou foi definida como nula antes de ser
passada para a função ft_lstadd_back. */

/* A segunda verificação, if (NULL == *lst), verifica se o ponteiro
apontado por lst (ou seja, o primeiro elemento da lista) é nulo.
Se for nulo, isso significa que a lista está vazia, então o novo
elemento new será adicionado como o primeiro elemento da lista, e
não como o último. */