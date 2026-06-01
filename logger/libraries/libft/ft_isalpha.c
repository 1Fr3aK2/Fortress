/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:52 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:37:14 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/* int main()
{
 	int c = 'k';
	int e = '9';
	int u = ' ';
	int p = '\n';
	int j = '0';
	int l = '\0';

	printf("%d\n", ft_isalpha(c));
	printf("%d\n", ft_isalpha(e));
	printf("%d\n", ft_isalpha(u));
	printf("%d\n", ft_isalpha(p));
	printf("%d\n", ft_isalpha(j));
	printf("%d\n", ft_isalpha(l));
 	return (0);
}  */