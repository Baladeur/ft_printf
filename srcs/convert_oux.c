/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_oux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:57:57 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/10 16:04:18 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*check_exception_octal(char *str, int *tab)
{
	if (str[0] == '0')
	{
		if (!tab[4] && !tab[1])
		{
			free(str);
			if (!(str = (char *)malloc(sizeof(char))))
				return (NULL);
			str[0] = '\0';
		}
		else
			tab[4] = 0;
	}
	else if (tab[4] && tab[1] > (int)ft_strlen(str))
		tab[1] -= 1;
	return (str);
}

static char	*check_exception_0(char *str, int *tab, char id)
{
	if (str[0] == '0' && id != 'o')
	{
		tab[4] = 0;
		if (!tab[1] || (id == 'o' && !tab[1]))
		{
			free(str);
			if (!(str = (char *)malloc(sizeof(char))))
				return (NULL);
			str[0] = '\0';
		}
	}
	else if (id == 'o')
		str = check_exception_octal(str, tab);
	return (str);
}

static char	*gather_arg(va_list arglist, int *tab, char id, int *len)
{
	char	*base;
	char	*str;

	base = ft_getbase(id);
	str = NULL;
	str = tab[3] == 'i' ? ft_itobase_hh(va_arg(arglist, int), base) : str;
	str = tab[3] == 'h' ? ft_itobase(
			(unsigned int)((unsigned short int)va_arg(arglist, unsigned int)),
			base) : str;
	str = !(tab[3]) ? ft_itobase(va_arg(arglist, unsigned int),
			base) : str;
	str = tab[3] == 'l' ? ft_itobase_l(va_arg(arglist, unsigned long int),
			base) : str;
	str = tab[3] == 'm' ? ft_itobase_ll(va_arg(arglist, unsigned long long int),
			base) : str;
	if (!str || !(str = check_exception_0(str, tab, id)))
		return (NULL);
	len[0] = ft_strlen(str);
	len[1] = biggest_int(3, len[0] + tab[4], tab[0], tab[1] + tab[4]);
	len[2] = 0;
	if (tab[1] > len[0])
		len[2] = tab[1] - len[0];
	free(base);
	return (str);
}

static void	set_prefix(char *str, int *tab, char id, int *len)
{
	if (tab[4] && tab[2])
		str[0] = '0';
	if (tab[4] > 1 && tab[2])
		str[1] = id;
	if (tab[4] && !tab[2])
		str[len[1] - len[0] - len[2] - tab[4]] = '0';
	if (tab[4] > 1 && !tab[2])
		str[len[1] - len[0] - len[2] - 1] = id;
	if (tab[2] == '0')
		ft_strnset(str + tab[4], '0', len[1] - len[0] - tab[4]);
	if (tab[2] == '-' && tab[1] > 0)
		ft_strnset(str + tab[4], '0', len[2]);
	else if (tab[1] > 0)
		ft_strnset(str + len[1] - len[0] - len[2], '0', len[2]);
}

char		*convert_unsigned(va_list arglist, t_printable *args, int *tab,
		char id)
{
	char	*str;
	char	*arg;
	int		len[3];

	if (!(arg = gather_arg(arglist, tab, id, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	if (tab[2] == '-')
		ft_strncpy(str + tab[4] + len[2], arg, len[0]);
	else
		ft_strncpy(str + len[1] - len[0], arg, len[0]);
	set_prefix(str, tab, id, len);
	args->len_str = len[1];
	free(arg);
	return (str);
}
