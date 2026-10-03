/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:15:16 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:38:00 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* int main()
{	

 	int c = 'k';
	int e = 'R';
	int y = '1';
	int o = '0';
	int t = '\0';
	int u = '\n';
	int g = '\t';

 	printf("%d\n", ft_isascii(c));
	printf("%d\n", ft_isascii(e));
	printf("%d\n", ft_isascii(y));
	printf("%d\n", ft_isascii(o));
	printf("%d\n", ft_isascii(t));
	printf("%d\n", ft_isascii(u));
	printf("%d\n", ft_isascii(g));
	return (0);
} */
