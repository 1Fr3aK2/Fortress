/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:09:32 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:36:42 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || (ft_isalpha(c)))
		return (1);
	return (0);
}

/* int main()
{
 	int c = 'k';
	int e = '9';
	int u = ' ';
	int p = '\n';

	printf("%d\n", ft_isalnum(c));
	printf("%d\n", ft_isalnum(e));
	printf("%d\n", ft_isalnum(u));
	printf("%d\n", ft_isalnum(p));
 	return (0);
} */