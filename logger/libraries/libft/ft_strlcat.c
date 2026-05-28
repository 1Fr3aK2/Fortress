/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:38:39 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 11:03:56 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	j;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = dest_len;
	j = 0;
	if (size <= dest_len)
		return (size + src_len);
	while (src[j] && (i + j) < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest_len + src_len);
}
/* int main()
{
	char src[15] = "hello world";
	char dest[20] = "asd";
	size_t result;
	size_t result1;

	printf("Dest before concatenation: %s\n", dest);
	printf("Concatenated string: %s\n", src);
	result = ft_strlcat(dest, src, 3);
	printf("Dest after concatenation: %s\n", dest);
	printf("Length of concatenation: %d\n", result);
	return (0);
} */

// A função strlcat retorna o comprimento
// total da string resultante após a concatenação.
