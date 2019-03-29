/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:09:36 by tferrieu          #+#    #+#             */
/*   Updated: 2019/03/29 14:43:56 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	*scan_flags(char *flags)
{
	int i;
	int	p;
	int	*tab;

	if (!(tab = (int *)malloc(sizeof(int) * 2)))
		return (NULL);
	tab[0] = 1;
	tab[1] = 0;
	p = 0;
	i = 0;
	while (flags[i])
	{
		if (flags[i] > '0' && flags[i] <= '9' && !p && tab[0] == 1)
			tab[0] = ft_atoi(flags + i);
		else if (flags[i] == '.' && !p && tab[0] == 1)
			p = 1;
		else if (flags[i] == '-')
			tab[1] = '-';
		else if (flags[i] == '0' && tab[1] != '-' && tab[0] == 1)
			tab[1] = '0'
		i++;
	}
	return (tab);
}

char		*convert_char(va_list arglist, t_printable *args, char *flag, int p)
{
	char	*str;
	int		*tab;
	int		i;

	if (!(tab = scan_flags(flag)))
		return (NULL);
	if (!(str = ft_strmake(' ', tab[0])))
		return (NULL);
	if (tab[1] == '0')
		ft_strnset(str, '0', tab[0] - 1);
	if (tab[1] == '-')
		str[0] = p ? va_arg(arglist, int) : '%';
	else
		str[tab[0] - 1] = p ? va_arg(arglist, int) : '%';
	args->len_str = tab[0];
	return (str);
}
