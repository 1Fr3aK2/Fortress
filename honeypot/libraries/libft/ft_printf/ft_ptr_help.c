/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:58:29 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 12:58:29 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(unsigned long int n, int *counter)
{
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 16)
		ft_putchar(symbols[n], counter);
	else
	{
		ft_putptr(n / 16, counter);
		ft_putptr(n % 16, counter);
	}
}

void	ft_ptr(unsigned long int ptr, int *counter)
{
	if (!ptr)
		ft_putstr("(nil)", counter);
	else
	{
		ft_putstr("0x", counter);
		ft_putptr(ptr, counter);
	}
}

/* int main()
{
	int counter;

  printf("%x\n", INT_MIN);
  counter = ft_putptr(INT_MIN, &counter);
  printf("%d\n",counter);
} */