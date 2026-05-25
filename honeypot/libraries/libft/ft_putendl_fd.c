/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:33:02 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/23 15:39:49 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Outputs the string ’s’ to the given file descriptor
followed by a newline.

Return value: None */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

/* int main()
{
	char *s;

	s = "lasbnda";
	ft_putendl_fd(s, 1);
	return (0);
} */