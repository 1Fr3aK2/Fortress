/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:23 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 10:40:57 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s)
        return (NULL);
	dest = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i])
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}
/* int main()
{
	const char *src = "Hello world!";
	char *dest;

	dest = ft_strdup(src);
	if (!dest)
	{
		printf("%s Memory allocation failed!\n");
		return (1);
	}
	else
	{
		printf("String original: %s\n", src);
		printf("String copiada: %s\n", dest);
		free(dest);
	}
	return (0);
} */
