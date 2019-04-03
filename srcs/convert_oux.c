/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_oux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:57:57 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/02 22:48:24 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	*scan_loop(int *tab, char *flags, int *i)
{
	while (flags[*i])
	{
		if (flags[*i] == 'h' && flags[*i + 1] == 'h' && tab[3] == 0)
			tab[3] = 'h' + 1;
		else if (flags[*i] == 'l' && flags[*i + 1] == 'l' && tab[3] == 0)
			tab[3] = 'l' + 1;
		else if (flags[*i] == 'h' && tab[3] == 0)
			tab[3] = 'h';
		else if (flags[*i] == 'l' && tab[3] == 0)
			tab[3] = 'l';
		else if (flags[*i] == '-')
			tab[1] = '-';
		else if (flags[*i] == '0' && tab[1] == 0 && tab[0] == -1)
			tab[1] = '0';
		else if (flags[*i] == '#')
			tab[2] = '#';
		else if (flags[*i] > '0' && flags[*i] <= '9' && tab[4] == 0)
		{
			tab[0] = ft_atoi(flags + *i);
			*i += ft_getpow(tab[0], 10) - 1;
		}
		else if (flags[*i] == '.')
			tab[4] = 1;
		*i += 1;
	}
}

static int	*scan_flags(char *flags)
{
	int	*tab;
	int i;

	if (!(tab = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	i = 0;
	tab[0] = -1;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	scan_loop(tab, flags, &i);
	return (tab);
}

static char	*gather_arg(va_list arglist, int *tab, char id, int *len)
{
	char	**base;
	char	*str;
	int		i;

	base = {"01234567", "0123456789", "0123456789abcdef", "0123456789abcdef"};
	i = id == 'o' ? 0 : 3;
	i = id == 'u' ? 1 : i;
	i = id == 'x' ? 2 : i;
	str = NULL;
	str = tab[3] == 'h' + 1 ? ft_itobase_hh(va_arg(arglist, base[i])) : str;
}

char		*convert_unsigned(va_list arglist, t_printable *args, char *flags,
								char id)
{
	char	*str;
	char	*arg;
	int		*tab;
	int		len[2];

	if (!(tab = scan_flags(flags)))
		return (NULL);
	if (!(arg = gather_arg(arglist, tab, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', total_len)))
		return (NULL);
	args->len_str = 5;
	free(tab);
	return (str);
}
