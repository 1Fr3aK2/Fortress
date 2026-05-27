/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:11:59 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/26 10:32:14 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	counter;

	if (!str)
		return (-1);
	number = 0;
	counter = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			counter = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (number * counter);
}

/* int main()
{
	char c[] = "------++++sdasd1321--654";
	char y[] = "+321321";
	char z[] = "-543651";
	char t[] = "+-654";
	char e[] = "-as4654";

	printf("%d\n", ft_atoi(c));
	printf("%d\n", ft_atoi(y));
	printf("%d\n", ft_atoi(z));
	printf("%d\n", ft_atoi(t));
	printf("%d\n", ft_atoi(e));
	return (0);
} */