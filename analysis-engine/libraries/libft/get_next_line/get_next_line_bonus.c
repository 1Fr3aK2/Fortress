/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:22:01 by marvin            #+#    #+#             */
/*   Updated: 2024/05/30 18:58:56 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	line[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*gnl;
	int			bytes_read;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	gnl = malloc(1 * sizeof(char));
	if (!gnl)
		return (NULL);
	gnl[0] = '\0';
	gnl = ft_strjoin(gnl, line[fd]);
	if (check_and_clear(line[fd]) == 1)
		return (gnl);
	bytes_read = read(fd, line[fd], BUFFER_SIZE);
	if (bytes_read <= 0 && (!*gnl))
		return (free_gnl(gnl));
	while (bytes_read > 0)
	{
		line[fd][bytes_read] = '\0';
		gnl = ft_strjoin(gnl, line[fd]);
		if (check_and_clear(line[fd]) == 1)
			break ;
		bytes_read = read(fd, line[fd], BUFFER_SIZE);
	}
	return (gnl);
}

/* int main()
{
    int fd1, fd2, fd3;
    char *line;

    fd1 = open("example.txt", O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening example.txt");
        return (1);
    }
    fd2 = open("example2.txt", O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening example2.txt");
        close(fd1);
        return (1);
    }
    fd3 = open("example3.txt", O_RDONLY);
    if (fd3 < 0)
    {
        perror("Error opening example3.txt");
        close(fd1);
        close(fd2);
        return (1);
    }
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    while ((line = get_next_line(fd2)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    while ((line = get_next_line(fd3)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
} */