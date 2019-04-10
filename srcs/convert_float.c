/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:28:20 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/10 20:04:43 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ftoa_custom2(long double n, int *tab, int p, int j)
{
	char	*str;
	int		k;
	int		i;

	if ((k = p) >= 0 && n == 0.0)
	{
		str = ft_strmake('0', tab[1] + 2 - !(tab[1] || tab[4]));
		if (str[1])
			str[1] = '.';
		tab[5] = !(1 / n > 0) ? '-' : tab[5];
		return (str);
	}
	if (!(str = ft_strmake(' ', p - j + tab[1] + 1 + (tab[1] > j)
										- !(tab[1] || tab[4]))))
		return (NULL);
	i = -1;
	while (str[++i] && i <= p)
	{
		str[i] = (long long int)(n / (long double)ft_pow_u(10, --k)) % 10 + 48;
		if (k == (j - (tab[1] > j)) && str[++i])
			str[i] = '.';
	}
	while (str[i])
		str[i++] = '0';
	return (str);
}

static char	*ftoa_custom(va_list arglist, int *tab)
{
	long double n;
	long double tmp;
	int			k;
	int			p;

	if ((p = 1) > 0 && tab[6] == 'L')
		n = (long double)(va_arg(arglist, long double));
	else
		n = (long double)(va_arg(arglist, double));
	if (n < 0. && (tab[5] = '-'))
		n *= -1.;
	if (n >= 1.0 / 0.0 && n <= 1.0 / 0.0)
		return (ft_strdup("inf"));
	if (n != n)
		return (ft_strdup("nan"));
	tab[1] = tab[1] < 0 ? 6 : tab[1];
	k = 0;
	while (k < tab[1] && ++k && n != (long double)((long long int)n))
		n *= 10.;
	if (n - (long double)((long long int)n) > 0.5)
		n += 1.;
	tmp = n;
	while (tmp >= 10. && ++p)
		tmp /= 10.;
	return (ftoa_custom2(n, tab, p, k));
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
