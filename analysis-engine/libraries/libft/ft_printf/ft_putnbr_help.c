/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:58:42 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 12:58:42 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long int nb, int *counter)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', counter);
		ft_putnbr(nb, counter);
	}
	else if (nb <= 9)
		ft_putchar(nb + 48, counter);
	else
	{
		ft_putnbr(nb / 10, counter);
		ft_putnbr(nb % 10, counter);
	}
}

void	ft_putnbr_base_x(unsigned int nb, int *counter)
{
	char	*symbols;

	symbols = "0123456789abcdef";
	if (nb < 16)
		ft_putchar(symbols[nb], counter);
	else
	{
		ft_putnbr_base_x(nb / 16, counter);
		ft_putnbr_base_x(nb % 16, counter);
	}
}

void	ft_putnbr_base_x_upper(unsigned int nb, int *counter)
{
	char	*symbols;

	symbols = "0123456789ABCDEF";
	if (nb < 16)
		ft_putchar(symbols[nb], counter);
	else
	{
		ft_putnbr_base_x_upper(nb / 16, counter);
		ft_putnbr_base_x_upper(nb % 16, counter);
	}
}

void	ft_putnbr_u(unsigned int nb, int *counter)
{
	if (nb <= 9)
		ft_putchar(nb += 48, counter);
	else
	{
		ft_putnbr_u(nb / 10, counter);
		ft_putnbr_u(nb % 10, counter);
	}
}

/*  int	main(void)
 {
	int counter;

	counter = ft_putnbr(-1, &counter);
	printf("\n");
	printf("%d", counter);

} */