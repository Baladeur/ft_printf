/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_oux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:57:57 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/04 17:46:37 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	scan_loop(int *tab, char *flags, int *i, int id)
{
	tab[3] = flags[*i] == 'h' && flags[*i + 1] == 'h' && !tab[3] ? 'i' : tab[3];
	tab[3] = flags[*i] == 'l' && flags[*i + 1] == 'l' && !tab[3] ? 'm' : tab[3];
	tab[3] = flags[*i] == 'h' && !tab[3] ? 'h' : tab[3];
	tab[3] = flags[*i] == 'l' && !tab[3] ? 'l' : tab[3];
	if (flags[*i] == '-')
		tab[1] = '-';
	else if (flags[*i] == '0' && tab[1] == 0 && tab[4] < 0)
		tab[1] = '0';
	else if (flags[*i] == '#' && id != 'u')
		tab[2] = '#';
	else if (flags[*i] > '0' && flags[*i] <= '9')
	{
		tab[0] = ft_atoi(flags + *i);
		*i += ft_getpow(tab[0], 10) - 1;
	}
	else if (flags[*i] == '.' && flags[*i + 1] >= '0' && flags[*i + 1] <= '9')
	{
		tab[4] = ft_atoi(flags + *i + 1);
		*i += ft_getpow(tab[4], 10);
	}
	else if (flags[*i] == '.')
		tab[4] = 0;
	if (tab[1] == '0' && tab[4] >= 0)
		tab[1] = 0;
}

static int	*scan_flags(char *flags, int id)
{
	int	*tab;
	int i;

	if (!(tab = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	i = 0;
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = -1;
	while (flags[i])
	{
		scan_loop(tab, flags, &i, id);
		i++;
	}
	if (tab[2])
	{
		tab[2] = id == 'x' || id == 'x' ? 2 : tab[2];
		tab[2] = id == 'o' ? 1 : tab[2];
	}
	return (tab);
}

static char	*gather_arg(va_list arglist, int *tab, char id, int *len)
{
	char	*base;
	char	*str;

	base = ft_getbase(id);
	str = NULL;
	str = tab[3] == 'i' ? ft_itobase_hh(va_arg(arglist, int), base) : str;
	str = tab[3] == 'h' || !(tab[3]) ? ft_itobase(va_arg(arglist, unsigned int),
			base) : str;
	str = tab[3] == 'l' ? ft_itobase_l(va_arg(arglist, unsigned long int),
			base) : str;
	str = tab[3] == 'm' ? ft_itobase_ll(va_arg(arglist, unsigned long long int),
			base) : str;
	len[0] = ft_strlen(str);
	len[1] = biggest_int(3, len[0] + tab[2], tab[0], tab[4] + tab[2]);
	len[2] = 0;
	if (tab[4] > len[0])
		len[2] = tab[4] - len[0];
	free(base);
	return (str);
}

static void	set_prefix(char *str, int *tab, char id, int *len)
{
	if (tab[2] && tab[1])
		str[0] = '0';
	if (tab[2] > 1 && tab[1])
		str[1] = id;
	if (tab[2] && !tab[1])
		str[len[1] - len[0] - len[2] - tab[2]] = '0';
	if (tab[2] > 1 && !tab[1])
		str[len[1] - len[0] - len[2] - 1] = id;
	if (tab[1] == '0')
		ft_strnset(str + tab[2], '0', len[1] - len[0] - tab[2]);
	if (tab[1] == '-' && tab[4] > 0)
		ft_strnset(str + tab[2], '0', len[2]);
	else if (tab[4] > 0)
		ft_strnset(str + len[1] - len[0] - len[2], '0', len[2]);
}

char		*convert_unsigned(va_list arglist, t_printable *args, char *flags,
		char id)
{
	char	*str;
	char	*arg;
	int		*tab;
	int		len[3];

	if (!(tab = scan_flags(flags, id)))
		return (NULL);
	if (!(arg = gather_arg(arglist, tab, id, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	if (tab[1] == '-')
		ft_strncpy(str + tab[2] + len[2], arg, len[0]);
	else
		ft_strncpy(str + len[1] - len[0], arg, len[0]);
	set_prefix(str, tab, id, len);
	free(tab);
	args->len_str = len[1];
	return (str);
}
