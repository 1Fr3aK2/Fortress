/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:00:11 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 11:22:07 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*mem;
	const unsigned char	*temp;

	temp = src;
	mem = dest;
	if (src == NULL && dest == NULL)
		return (dest);
	if (n == 0)
		return (dest);
	if (dest > src)
	{
		while (n-- > 0)
			mem[n] = temp[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/* int main() {
	// Teste 1: Ambos src e dest são NULL
	char *src1 = NULL;
	char *dest1 = NULL;
	size_t n1 = 5;

	printf("Teste 1:\n");
	printf("Before ft_memmove: src='%s', dest='%s'\n", src1, dest1);
	ft_memmove(dest1, src1, n1);
	printf("After ft_memmove: src='%s', dest='%s'\n\n", src1, dest1);


	// Teste 3: n é válido
	printf("Teste 3:\n");
	char src3[] = "Source";
	char dest3[] = "trq";
	size_t n3 = 3;
	printf("Before ft_memmove: src='%s', dest='%s'\n", src3, dest3);
	ft_memmove(dest3, src3, n3);
	printf("After ft_memmove: src='%s', dest='%s'\n\n", src3, dest3);

	return (0);
}  */