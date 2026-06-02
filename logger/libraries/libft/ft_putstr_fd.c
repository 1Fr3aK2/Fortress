/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:14:41 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/22 10:55:17 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Outputs the string ’s’ to the given file
descriptor.

Return: value None */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/* int main()
{	
	char *s;

	s = "test string";
	ft_putstr_fd(s, 1);
	return (0);
} */
