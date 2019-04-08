/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:54:02 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 19:18:45 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	length_modif(const char *restrict format, int *tab, char c, int *i)
{
	if (c == 'l')
	{
		if (format[*i + 1] == 'l')
		{
			tab[3] = 'm';
			*i += 1;
		}
		else
			tab[3] = 'l';
	}
	if (c == 'h')
	{
		if (format[*i + 1] == 'h')
		{
			tab[3] = 'i';
			*i += 1;
		}
		else
			tab[3] = 'h';
	}
}

void		update_flags(const char *restrict format, int *tab, char c, int *i)
{
	if (c > '0' && c <= '9')
	{
		tab[0] = ft_atoi(format + *i);
		*i += ft_getpow(tab[0], 10) - 1;
	}
	else if (c == '.')
	{
		tab[1] = ft_atoi(format + *i + 1);
		if (format[*i + 1] >= '0' && format[*i + 1] <= '9')
			*i += ft_getpow(tab[1], 10);
	}
	else if (c == '0' && !tab[2])
		tab[2] = '0';
	else if (c == '-')
		tab[2] = '-';
	else if (c == '+')
		tab[5] = '+';
	else if (c == ' ' && !tab[5])
		tab[5] = ' ';
	else if (c == '#')
		tab[4] = '#';
	else if ((c == 'l' || c == 'h') && !tab[3])
		length_modif(format, tab, c, i);
	*i += 1;
}
