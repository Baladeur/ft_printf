/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:28:20 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/09 22:13:48 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ftoa_custom2(long long int n, int *tab, int p)
{
	char	*str;
	int		k;
	int		i;

	if (!(str = ft_strmake(' ', p + 1 - !(tab[1] || tab[4]))))
		return (NULL);
	k = p;
	i = 0;
	while (str[i])
	{
		str[i] = (n / ft_pow(10, k - 1)) % 10 + 48;
		k--;
		if (k == tab[1] && str[++i])
			str[i] = '.';
		i++;
	}
	return (str);
}

static char	*ftoa_custom(va_list arglist, int *tab)
{
	long double n;
	long double tmp;
	int			k;
	int			p;

	if (tab[6] == 'l')
		n = (long double)(va_arg(arglist, double));
	else if (tab[6] == 'L')
		n = (long double)(va_arg(arglist, long double));
	else
		n = (long double)((float)va_arg(arglist, double));
	if (n < 0. && (tab[5] = '-'))
		n *= -1.;
	if (tab[1] < 0)
		tab[1] = 6;
	k = 0;
	while (k < tab[1] && ++k)
		n *= 10.;
	if (n - (long double)((long long int)n) > 0.5)
		n += 1.;
	tmp = n;
	p = 1;
	while (tmp >= 10. && ++p)
		tmp /= 10.;
	return (ftoa_custom2((long long int)n, tab, p));
}

static char	*gather_arg(va_list arglist, int *tab, int *len)
{
	char	*str;
	int		t;

	str = ftoa_custom(arglist, tab);
	t = (tab[5] > 0);
	len[0] = ft_strlen(str);
	len[1] = biggest_int(2, len[0] + t, tab[0]);
	return (str);
}

char		*convert_float(va_list arglist, t_printable *args, int *tab)
{
	char	*str;
	char	*arg;
	int		len[2];

	if (!(arg = gather_arg(arglist, tab, len)))
		return (0);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	if (tab[2] && tab[5])
		str[0] = (char)tab[5];
	else if (tab[5])
		str[len[1] - len[0] - 1] = (char)tab[5];
	if (tab[2] == '0')
		ft_strnset(str + (tab[5] > 0), '0', len[1] - len[0] - (tab[5] > 0));
	if (tab[2] == '-')
		ft_strncpy(str + (tab[5] > 0), arg, len[0]);
	else
		ft_strncpy(str + len[1] - len[0], arg, len[0]);
	free(arg);
	args->len_str = len[1];
	return (str);
}
