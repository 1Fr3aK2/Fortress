/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:58:49 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 12:58:49 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *counter)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		*counter += 6;
		return ;
	}
	while (*str)
	{
		write(1, str++, 1);
		(*counter)++;
	}
}

/* int main()
{
	int counter;
	char *str = "adas";

	counter = ft_putstr(str, &counter);
	printf("\n");
	printf("%d", counter);
	return (0);
} */