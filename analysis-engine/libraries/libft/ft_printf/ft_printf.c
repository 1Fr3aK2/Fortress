/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/05/08 13:36:46 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 13:36:46 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char c, va_list *ap)
{
	int		chars;

	chars = 0;
	if (c == 'c')
		ft_putchar(va_arg(*ap, int), &chars);
	else if (c == 's')
		ft_putstr(va_arg(*ap, char *), &chars);
	else if (c == 'p')
		ft_ptr(va_arg(*ap, unsigned long int), &chars);
	else if (c == 'd' || c == 'i')
		ft_putnbr((long)(va_arg(*ap, int)), &chars);
	else if (c == 'u')
		ft_putnbr_u(va_arg(*ap, unsigned int), &chars);
	else if (c == 'x')
		ft_putnbr_base_x((long)(va_arg(*ap, unsigned int)), &chars);
	else if (c == 'X')
		ft_putnbr_base_x_upper((long)(va_arg(*ap, unsigned int)), &chars);
	else if (c == '%')
		ft_putchar('%', &chars);
	return (chars);
}

static int	verify(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			counter;

	counter = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (verify(FLAGS, (*(str + 1))))
			{
				str++;
				counter += print_format(*str, &ap);
			}
			else if (*(str + 1) == '\0')
				return (-1);
		}
		else
			counter += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (counter);
}
