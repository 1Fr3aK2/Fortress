/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:00 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:18:53 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	c1;
	int		i;

	i = 0;
	c1 = (char)c;
	str = (char *)s;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == c1)
			return (str + i);
		i--;
	}
	return (NULL);
}
/* int	main(void)
{
	char *str = "teste string";
	int c = 'p';
	char *result;

	result = ft_strrchr(str, c);
	if (result)
		printf("O carater '%c' foi encontrado na string, resultado: %s\n", c,
			result);
	else
		printf("O carater '%c' nao foi encontrado na string, resultado: %s\n",
			c, result);
	return (0);
} */
