/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:58:36 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 12:58:36 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

/* int main()
{
	int counter;

	counter = ft_putchar('%');
	printf("\n");
	printf("%d", counter);
} */