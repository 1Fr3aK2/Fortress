/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:20:06 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 15:49:00 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	char	*s1;
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	s1 = (char *)str;
	while (i < n)
	{
		if (s1[i] == c)
			return (s1 + i);
		i++;
	}
	return (NULL);
}
/* int main()
{
	char c[20] = "test string\n";

	printf("%s", ft_memchr(c, 't',  11));
	return (0);
} */