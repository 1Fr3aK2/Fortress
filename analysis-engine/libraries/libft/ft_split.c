/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:05:02 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 11:37:35 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.

Return value: The array of new strings resulting from the split.
NULL if the allocation fails. */

#include "libft.h"

// contar palavras
static int	count_word(const char *str, char c)
{
	int	i;
	int	words;

	if (!str)
		return (-1);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}
// alocar memoria

static char	*word_aloc(const char *str, char c)
{
	char	*word;
	int		word_len;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (NULL);
	while (++i < word_len)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			dest[i] = word_aloc(s, c);
			if (!dest[i++])
				return (free_str(dest, i - 1), NULL);
		}
		while (*s && *s != c)
			s++;
	}
	dest[i] = 0;
	return (dest);
}
// int main()
// {
//     const char *str = "hello  world";
//     char delimiter = ' ';

//     // Chama a função ft_split para dividir a string
//     char **tokens = ft_split(str, delimiter);

//     if (tokens)
// 	{
//         printf("Tokens:\n");
//         // Imprime os tokens resultantes
//         for (int i = 0; tokens[i] != NULL; i++)
//             printf("%s\n", tokens[i]);

//         // Libera a memória alocada dinamicamente
//         free_str(tokens, count_word(str, delimiter));
//     }
// 	else
//         printf("Falha ao dividir a string.\n");
// }