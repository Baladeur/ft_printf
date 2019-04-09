/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:41:24 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/09 18:47:57 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
	tab[5] = n < 0 ? '-' : tab[5];
	return (ft_itobase_ll(ft_abs_ll(n), "0123456789"));
}

static char	*check_exception_0(char *str, int *tab)
{
	if (str[0] == '0')
	{
		if (!(tab[5] == '+' || tab[5] == ' '))
			tab[2] = 0;
		if (!tab[1])
		{
			free(str);
			if (!(str = (char *)malloc(sizeof(char))))
				return (NULL);
			str[0] = '\0';
		}
	}
	return (str);
}

static char	*gather_arg(va_list arglist, int *tab, int *len)
{
	char	*str;
	int		t;

	str = itoa_custom(tab, arglist);
	if (!(str = check_exception_0(str, tab)))
		return (NULL);
	t = (tab[5] > 0);
	len[0] = ft_strlen(str);
	len[1] = biggest_int(3, len[0] + t, tab[0], tab[1] + t);
	len[2] = 0;
	if (tab[1] > len[0])
		len[2] = tab[1] - len[0];
	return (str);
}

char		*convert_int(va_list arglist, t_printable *args, int *tab)
{
	char	*str;
	char	*arg;
	int		len[3];

	if (!(arg = gather_arg(arglist, tab, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	ft_strncpy(tab[2] == '-'
			? str + (tab[5] > 0) + len[2] : str + len[1] - len[0], arg, len[0]);
	str[0] = tab[5] && tab[2] ? (char)tab[5] : str[0];
	if (tab[5] && !tab[2])
		str[len[1] - len[0] - len[2] - 1] = (char)tab[5];
	if (tab[2] == '0')
		ft_strnset(str + (tab[5] > 0), '0', len[1] - len[0] - (tab[5] > 0));
	if ((args->len_str = len[1]) >= 0 && tab[2] == '-' && tab[1] > 0)
		ft_strnset(str + (tab[5] > 0), '0', len[2]);
	else if (tab[1] > 0)
		ft_strnset(str + len[1] - len[0] - len[2], '0', len[2]);
	free(arg);
	return (str);
}
