/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_csp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:56:04 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 15:58:28 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	scan_flags(char *flags, int t, int *tab)
{
	int i;

	tab[0] = t;
	tab[1] = 0;
	tab[2] = -1;
	i = -1;
	while (flags[++i])
	{
		tab[2] = flags[i] == '.' ? 0 : tab[2];
		tab[1] = flags[i] == '-' ? '-' : tab[1];
		tab[1] = flags[i] == '0' && !tab[1] ? '0' : tab[1];
		if (flags[i] > '0' && flags[i] <= '9' && tab[2] < 0)
		{
			tab[0] = ft_atoi(flags + i);
			i += ft_getpow(tab[0], 10) - 1;
		}
		else if (flags[i] == '.' && flags[i + 1] >= '0' && flags[i + 1] <= '9')
		{
			tab[2] = ft_atoi(flags + i + 1);
			i += ft_getpow(tab[2], 10);
		}
	}
}

char		*convert_char(va_list arglist, t_printable *args, char *flag, int p)
{
	char	*str;
	int		tab[3];

	scan_flags(flag, 1, tab);
	if (!(str = ft_strmake(' ', tab[0])))
		return (NULL);
	if (tab[1] == '0')
		ft_strnset(str, '0', tab[0] - 1);
	if (tab[1] == '-')
		str[0] = p ? va_arg(arglist, int) : '%';
	else
		str[tab[0] - 1] = p ? va_arg(arglist, int) : '%';
	args->len_str = tab[0];
	if (flag)
		free(flag);
	return (str);
}

static char	*gather_arg(va_list arglist, int *tab, int *total_len, int *arg_len)
{
	char	*str;
	char	*arg;

	str = va_arg(arglist, char *);
	str = !str ? "(null)" : str;
	if (tab[2] > 0 && tab[2] < (int)ft_strlen(str))
	{
		if (!(arg = ft_strndup(str, tab[2])))
			return (NULL);
	}
	else
	{
		if (!(arg = ft_strdup(str)))
			return (NULL);
	}
	*arg_len = ft_strlen(arg);
	*total_len = *arg_len > tab[0] ? *arg_len : tab[0];
	return (arg);
}

char		*convert_str(va_list arglist, t_printable *args, char *flags)
{
	char	*str;
	char	*arg;
	int		tab[3];
	int		total_len;
	int		arg_len;

	scan_flags(flags, 0, tab);
	if (!(arg = gather_arg(arglist, tab, &total_len, &arg_len)))
		return (NULL);
	if (!(str = ft_strmake(' ', total_len)))
		return (NULL);
	if (tab[1] == '0')
		ft_strnset(str, '0', total_len - arg_len);
	if (tab[1] == '-')
		ft_strncpy(str, arg, arg_len);
	else
		ft_strncpy(str + total_len - arg_len, arg, arg_len);
	args->len_str = total_len;
	free(arg);
	if (flags)
		free(flags);
	return (str);
}

char		*convert_ptr(va_list arglist, t_printable *args, char *flags)
{
	char	*str;
	char	*arg;
	int		tab[3];
	int		len;

	scan_flags(flags, 0, tab);
	if (!(arg = ft_itobase_ll((unsigned long long int)va_arg(arglist, void *),
							"0123456789abcdef")))
		return (NULL);
	len = biggest_int(2, ft_strlen(arg) + 2, tab[0]);
	if (!(str = ft_strmake(' ', len)))
		return (NULL);
	if (tab[1] == '0')
		ft_strnset(str + 2, '0', len - ft_strlen(arg) - 2);
	if (tab[1] == '0' || tab[1] == '-')
		ft_strncpy(str, "0x", 2);
	else
		ft_strncpy(str + len - ft_strlen(arg) - 2, "0x", 2);
	if ((args->len_str = len) >= 0 && tab[1] == '-')
		ft_strncpy(str + 2, arg, ft_strlen(arg));
	else
		ft_strncpy(str + len - ft_strlen(arg), arg, ft_strlen(arg));
	free(arg);
	if (flags)
		free(flags);
	return (str);
}
