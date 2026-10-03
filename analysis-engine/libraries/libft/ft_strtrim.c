/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:21:28 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 20:45:09 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.

Return value: The trimmed string.
NULL if the allocation fails. */

// só remove os do inicio ou fim

#include "libft.h"

static int	is_char(const char *str, const char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*dest;

	i = 0;
	start = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && is_char(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_char(set, s1[end - 1]))
		end--;
	dest = (char *)malloc(end - start + 1);
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = s1[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
/* int main()
{
	char *str = "ana analfabeto anaconda antonio";
	char *set;
	char *new;


	printf("str before the trim: %s\n", str);
	new = ft_strtrim("ana analfabeto anaconda antonioa" , "a");
	printf("str after the trim: %s\n", new);
	free(new);
	return (0);
} */