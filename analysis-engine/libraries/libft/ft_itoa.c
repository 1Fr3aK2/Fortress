/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:06 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/23 15:23:35 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.

Return value: The string representing the integer.
NULL if the allocation fails. */

#include "libft.h"

static int	length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*print_char(char *str, long int n, int len)
{
	while (n > 0)
	{
		str[len--] = (n % 10) + 48;
		n = (n / 10);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*dest;
	long int	len;
	long int	nb;

	nb = n;
	len = length(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len--] = '\0';
	if (nb == 0)
		dest[0] = '0';
	if (nb < 0)
	{
		nb = nb * -1;
		dest[0] = '-';
	}
	dest = print_char(dest, nb, len);
	return (dest);
}

/*  int main()
{
	int n = INT_MIN;
	int j = INT_MAX;

	char *str = ft_itoa(n);
	char *str1 = ft_itoa(j);
	printf("%s\n", str);
	printf("%s\n", str1);
} */