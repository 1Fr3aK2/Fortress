/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:20:37 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:19:43 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;

	s1 = (char *)str1;
	s2 = (char *)str2;
	i = 0;
	if (*s2 == '\0')
		return (s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] && s2[j] && i + j < n)
		{
			if (s1[i + j] != s2[j])
				break ;
			j++;
			if (!s2[j])
				return (s1 + i);
		}
		i++;
	}
	return (NULL);
}
/*int main()
{
	char *str;
	char *str2;

	str = "hello worlde!";
	str2 = "lo";
	printf("%s\n", ft_strnstr(str, str2, 5));
	return (0);
}
ao usar o break sai do 2nd while loop */