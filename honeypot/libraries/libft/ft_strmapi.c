/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:55:08 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 10:52:47 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Applies the function f to each character of the
string s, passing its index as the first argument
and the character itself as the second. A new
string is created (using malloc(3)) to collect the
results from the successive applications of f.

Return value: The string created from the successive applications
of ’f’.
Returns NULL if the allocation fails */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/* char upper(unsigned int index, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}

int	main(void)
{
	char *str = "teste St4InG";

	printf("Original string: %s\n", str);
	char *new_str = ft_strmapi(str, &upper);
	printf("Modified string: %s\n", new_str);
	free(new_str);
	return (0);
} */
