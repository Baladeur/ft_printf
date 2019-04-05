/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:41:24 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/05 18:41:47 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	scan_loop(int *tab, char *flags, int *i)
{
	tab[3] = flags[*i] == 'h' && flags[*i + 1] == 'h' && !tab[3] ? 'i' : tab[3];
	tab[3] = flags[*i] == 'l' && flags[*i + 1] == 'l' && !tab[3] ? 'm' : tab[3];
	tab[3] = flags[*i] == 'h' && !tab[3] ? 'h' : tab[3];
	tab[3] = flags[*i] == 'l' && !tab[3] ? 'l' : tab[3];
	tab[2] = flags[*i] == ' ' && !tab[2] ? ' ' : tab[2];
	tab[2] = flags[*i] == '+' ? '+' : tab[2];
	if (flags[*i] == '-')
		tab[1] = '-';
	else if (flags[*i] == '0' && tab[1] == 0 && tab[4] < 0)
		tab[1] = '0';
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

static int	*scan_flags(char *flags)
{
	int	*tab;
	int	i;

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
		scan_loop(tab, flags, &i);
		i++;
	}
	return (tab);
}

static char	*itoa_custom(int *tab, va_list arglist)
{
	long long int n;

	n = 0;
	if (tab[3] == 'i')
		n = (long long int)((char)(va_arg(arglist, int)));
	else if (tab[3] == 'h')
		n = (long long int)((short int)(va_arg(arglist, int)));
	else if (!tab[3])
		n = (long long int)(va_arg(arglist, int));
	else if (tab[3] == 'l')
		n = (long long int)(va_arg(arglist, long int));
	else if (tab[3] == 'm')
		n = va_arg(arglist, long long int);
	else
		return (NULL);
	tab[2] = n < 0 ? '-' : tab[2];
	return (ft_itobase_ll(ft_abs_ll(n), "0123456789"));
}

static char	*gather_arg(va_list arglist, int *tab, int *len)
{
	char	*str;
	int		t;

	str = itoa_custom(tab, arglist);
	if (!(str = check_exception_0(str, tab, 'i')))
		return (NULL);
	t = (tab[2] > 0);
	len[0] = ft_strlen(str);
	len[1] = biggest_int(3, len[0] + t, tab[0], tab[4] + t);
	len[2] = 0;
	if (tab[4] > len[0])
		len[2] = tab[4] - len[0];
	return (str);
}

char		*convert_int(va_list arglist, t_printable *args, char *flags)
{
	char	*str;
	char	*tmp;
	char	*arg;
	int		*tab;
	int		len[3];

	if (!(tab = scan_flags(flags)))
		return (NULL);
	if (!(arg = gather_arg(arglist, tab, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	tmp = tab[1] == '-' ? str + (tab[2] > 0) + len[2] : str + len[1] - len[0];
	ft_strncpy(tmp, arg, len[0]);
	str[0] = tab[2] && tab[1] ? (char)tab[2] : str[0];
	if (tab[2] && !tab[1])
		str[len[1] - len[0] - len[2] - 1] = (char)tab[2];
	if (tab[1] == '0')
		ft_strnset(str + (tab[2] > 0), '0', len[1] - len[0] - (tab[2] > 0));
	if ((args->len_str = len[1]) >= 0 && tab[1] == '-' && tab[4] > 0)
		ft_strnset(str + (tab[2] > 0), '0', len[2]);
	else if (tab[4] > 0)
		ft_strnset(str + len[1] - len[0] - len[2], '0', len[2]);
	free(tab);
	return (str);
}
