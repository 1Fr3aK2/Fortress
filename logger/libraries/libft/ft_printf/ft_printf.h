/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:58:11 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/08 12:58:11 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# define FLAGS "csdiupxX%"

void	ft_putptr(unsigned long int n, int *counter);
void	ft_ptr(unsigned long int ptr, int *counter);

void	ft_putchar(char c, int *counter);

void	ft_putstr(char *str, int *counter);

void	ft_putnbr(long int nb, int *counter);
void	ft_putnbr_base_x(unsigned int nb, int *counter);
void	ft_putnbr_base_x_upper(unsigned int nb, int *counter);
void	ft_putnbr_u(unsigned int n, int *counter);

int		print_format(char c, va_list *ap);
int		ft_printf(const char *str, ...);

#endif