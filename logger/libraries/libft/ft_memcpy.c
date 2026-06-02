/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:55 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 10:58:28 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*mem;
	const unsigned char	*old;
	size_t				i;

	i = 0;
	old = src;
	mem = dest;
	while (i < n && (src || dest))
	{
		mem[i] = old[i];
		i++;
	}
	return (dest);
}

/* int main()
{
	char src[] = "ola tudo bem";
	char dest[13] = "";

	printf("%s\n", ft_memcpy(dest, src, 7));
	return (0);
} */
