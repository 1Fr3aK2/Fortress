/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:30:16 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/16 12:08:11 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*mem;
	size_t			counter;

	counter = 0;
	mem = str;
	while (counter < n)
		mem[counter++] = c;
	return (str);
}

/* int main()
{
	char  str[10] = "trabalhop";
	
	printf("buffer antes de memset : %s\n", str);
	ft_memset(str, 't', 9);
	printf("buffer depois de memset : %s\n", str);

	return (0);
} */
