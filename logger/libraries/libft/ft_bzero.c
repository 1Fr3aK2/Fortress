/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:14:46 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/23 15:35:17 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*mem;
	size_t			counter;

	if (!str)
		return ;
	mem = str;
	counter = 0;
	while (counter < n)
		mem[counter++] = '\0';
}

/* int main()
{
	char buffer[50] = "kasbdijbas324as654654321asd";
	char ok[] = "45";
	char y[] = "          f  \n \t \r            ";
	char r[] = "\0";
	char e[] = "aksndpoansdn,ambsdlkbasl,ndlaknsldkbasldna"
	
	printf("buffer antes de ft_bzero: %s\n", buffer);
	printf("ok antes de ft_bzero: %s\n", ok);
	printf("y antes de ft_bzero: %s\n", y);
	printf("r antes de ft_bzero: %s\n", r);
	printf("e antes de ft_bzero: %s\n", e);
	ft_bzero(buffer, sizeof(buffer));
	ft_bzero(ok, sizeof(ok));
	ft_bzero(y, sizeof(y));
	ft_bzero(r, sizeof(r));
	ft_bzero(e, sizeof(e));
	printf("buffer depois de ft_bzero: %s\n", buffer);
	printf("ok depois de ft_bzero: %s\n", ok);
	printf("y depois de ft_bzero: %s\n", y);
	printf("r depois de ft_bzero: %s\n", r);
	printf("e depois de ft_bzero: %s\n", e);

	return (0);
} */