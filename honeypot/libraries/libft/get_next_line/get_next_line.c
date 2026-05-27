/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:39:56 by raamorim          #+#    #+#             */
/*   Updated: 2024/05/27 13:39:56 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	line[BUFFER_SIZE + 1];
	char		*gnl;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl = malloc(1 * sizeof(char));
	if (!gnl)
		return (NULL);
	gnl[0] = '\0';
	gnl = ft_strjoin(gnl, line);
	if (check_and_clear(line) == 1)
		return (gnl);
	bytes_read = read(fd, line, BUFFER_SIZE);
	if (bytes_read <= 0 && (!*gnl))
		return (free_gnl(gnl));
	while (bytes_read > 0)
	{
		line[bytes_read] = '\0';
		gnl = ft_strjoin(gnl, line);
		if (check_and_clear(line) == 1)
			break ;
		bytes_read = read(fd, line, BUFFER_SIZE);
	}
	return (gnl);
}

/* int main()
{
	int fd;
	char *line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}

	close(fd);
	return (0);
} */
