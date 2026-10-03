/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:30:16 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:08:08 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Description: Allocates (with malloc(3)) and returns a substring 
from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’. 

Return Value: The substring.
NULL if the allocation fails. */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str_copied;

	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	str_copied = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str_copied)
		return (NULL);
	while (i < len && s[i])
	{
		str_copied[i] = s[start + i];
		i++;
	}
	str_copied[i] = '\0';
	return (str_copied);
}

/*  int main()
 {
    char *test;

    test = ft_substr("cavalo de madeira", 3, 20);
     printf("%s\n", test);
     free(test);
     return (0);
 } */