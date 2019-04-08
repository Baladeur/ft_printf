/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:56:04 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 20:38:31 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*gather_arg(va_list arglist, int *tab, int *total_len, int *arg_len)
{
	char	*str;
	char	*arg;

	str = va_arg(arglist, char *);
	str = !str ? "(null)" : str;
	if (tab[1] > 0 && tab[1] < (int)ft_strlen(str))
	{
		if (!(arg = ft_strndup(str, tab[1])))
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

char		*convert_str(va_list arglist, t_printable *args, int *tab)
{
	char	*str;
	char	*arg;
	int		total_len;
	int		arg_len;

	if (!(arg = gather_arg(arglist, tab, &total_len, &arg_len)))
		return (NULL);
	if (!(str = ft_strmake(' ', total_len)))
		return (NULL);
	if (tab[2] == '0')
		ft_strnset(str, '0', total_len - arg_len);
	if (tab[2] == '-')
		ft_strncpy(str, arg, arg_len);
	else
		ft_strncpy(str + total_len - arg_len, arg, arg_len);
	args->len_str = total_len;
	free(arg);
	return (str);
}

char		*convert_char(va_list arglist, t_printable *args, int *tab, int p)
{
	char	*str;

	if (!(str = ft_strmake(' ', tab[0])))
		return (NULL);
	if (tab[2] == '0')
		ft_strnset(str, '0', tab[0] - 1);
	if (tab[2] == '-')
		str[0] = p ? va_arg(arglist, int) : '%';
	else
		str[tab[0] - 1] = p ? va_arg(arglist, int) : '%';
	args->len_str = tab[0];
	return (str);
}
