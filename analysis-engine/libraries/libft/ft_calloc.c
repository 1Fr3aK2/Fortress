/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:29:02 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/30 13:42:21 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;
	size_t	full_size;

	full_size = (count * size);
	if (full_size / size != count)
		return (NULL);
	dest = malloc(count * size);
	if (!dest)
		return (NULL);
	if (count == 0 || size == 0)
		return (dest);
	ft_bzero(dest, size * count);
	return (dest);
}

/* int main()
{
	int *buffer;
	int buffer_elements;
	int i;

	i = 0;
	buffer_elements = 5;
	buffer = (int *)ft_calloc(buffer_elements, sizeof(int));
	if (!buffer)
	{
		printf("Memory allocation failed!");
		return (1);
	}
	printf("Inicialized values:\n");
	while(i < buffer_elements)
	{
		printf("%d", buffer[i]);
		i++;
	}
	printf("\n");
	free(buffer);
	return(0);
} */
