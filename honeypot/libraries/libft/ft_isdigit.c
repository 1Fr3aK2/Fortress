/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:16 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 11:38:35 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
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

 	printf("%d\n", ft_isdigit(c));
	printf("%d\n", ft_isdigit(e));
	printf("%d\n", ft_isdigit(y));
	printf("%d\n", ft_isdigit(o));
	printf("%d\n", ft_isdigit(t));
	printf("%d\n", ft_isdigit(u));
	printf("%d\n", ft_isdigit(g));
	return (0);
} */