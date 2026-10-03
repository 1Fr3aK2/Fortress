/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:40 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:50:22 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

/* int main()
{
	char src[] = "Hello, world!"; 
	char dest[20] = "";
	size_t result;

	printf("Dest before copy: %s\n", dest);
	printf("Copied string: %s\n", src);
	result = ft_strlcpy(dest, src, sizeof(dest));
	printf("Length of src : %d\n", result);
	printf("dest after copy: %s\n", dest);
	return (0);

} */

// retorna o comp de src mesmo que nao exista espaco suficiete
// no buffer para copiar src completa