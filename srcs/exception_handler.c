/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:32:23 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/05 16:37:12 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*check_exception_0(char *str, int *tab, char id)
{
	if (str[0] == '0')
	{
		if (!(id == 'o' || tab[2] == '+' || tab[2] == ' '))
			tab[2] = 0;
		if (!tab[4])
		{
			free(str);
			if (!(str = (char *)malloc(sizeof(char))))
				return (NULL);
			str[0] = '\0';
		}
	}
	return (str);
}
