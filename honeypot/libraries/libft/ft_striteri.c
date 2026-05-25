/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:37:39 by raamorim          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:20 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.

Return value: None */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* void upper(unsigned int index, char *c) 
{
    if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

int main() {
    char str[] = "Hello, world!";
    
    printf("Original string : %s\n", str);
    ft_striteri(str, &upper);
    
    printf("Modified string: %s\n", str);
    return 0;
} */

// usar & porque queremos que o ponteiro
		//aponte para o adress do carater,

		// caso nao usasse & f nao seria capaz de
		// modificar o valor porque estaria a trabalhar
		//com uma "copia e nao com o real adree logo na
		// poderia mudar o seu real valor"