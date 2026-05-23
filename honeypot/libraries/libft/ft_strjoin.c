/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:10:19 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/18 14:15:06 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description:  Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation of ’s1’ and ’s2’.

Return value: The new string.
NULL if the allocation fails. */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/* int	main(void)
{
	char *test;

 	test = ft_strjoin("test", "string");
 	printf("%s\n", test);

 	free(test);
} */

/* int main()
{
	char *str;
	char *str1;
	char *result;

	str = "test string";
	str1 = "ola mundo";
	printf("str before join: %s\n", str);
	printf("str1 before join: %s\n", str1);
	result = ft_strjoin(str, str1);
	printf("Result of the joined strings: %s\n", result);
	free(result);
	return (0);
} */