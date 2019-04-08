/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:52:34 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 19:47:38 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	init_tab(int *tab)
{
	tab[0] = 0;
	tab[1] = -1;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
}

static char	*convert_core(va_list arglist, t_printable *args, int *tab,
		char id)
{
	if (id == 'c' || id == '%')
		return (convert_char(arglist, args, tab, id == 'c' ? 1 : 0));
	else if (ft_strchr("ouxX", id))
		return (convert_unsigned(arglist, args, tab, id));
	else if (id == 'i' || id == 'd')
		return (convert_int(arglist, args, tab));
	else if (id == 's')
		return (convert_str(arglist, args, tab));
	else if (id == 'p')
		return (convert_ptr(arglist, args, tab));
	else
		return (NULL);
}

static char	*identifier(const char *restrict format, va_list arglist,
		t_printable *args)
{
	int	tab[6];
	int	i;

	i = 1;
	init_tab(tab);
	while (format[i] && ft_strchr("hlL#0-+.123456789 ", format[i]))
		update_flags(format, tab, format[i], &i);
	if (!format[i] || !(ft_strchr("cspdiouxXf%hlL#0-+.123456789 ", format[i])))
	{
		args->len_flag = i;
		args->len_str = 0;
		return (ft_strnew(0));
	}
	if (tab[4] && (format[i] == 'o' || format[i] == 'x' || format[i] == 'X'))
		tab[4] = format[i] == 'o' ? 1 : 2;
	else
		tab[4] = 0;
	if (!tab[0] && (format[i] == 'c' || format[i] == '%'))
		tab[0] = 1;
	if (tab[2] == '0' && tab[1] >= 0)
		tab[2] = 0;
	args->len_flag = i + 1;
	return (convert_core(arglist, args, tab, format[i]));
}

static int	add_printable(const char *restrict format, int *len,
		va_list arglist, t_printable **args)
{
	t_printable *pos;

	if (!(*args))
	{
		if (!(*args = (t_printable *)malloc(sizeof(t_printable))))
			return (0);
		pos = *args;
	}
	else
	{
		pos = *args;
		while (pos->next)
			pos = pos->next;
		if (!(pos->next = (t_printable *)malloc(sizeof(t_printable))))
			return (0);
		pos = pos->next;
	}
	pos->str = NULL;
	pos->next = NULL;
	pos->len_flag = 0;
	pos->len_str = 0;
	if (!(pos->str = identifier(format + *len, arglist, pos)))
		return (0);
	*len += pos->len_flag;
	return (1);
}

int			parse(const char *restrict format, va_list arglist, int *len,
		t_printable **args)
{
	while (format[*len])
	{
		if (format[*len] == '%')
		{
			if (!(add_printable(format, len, arglist, args)))
				return (0);
		}
		else
			*len += 1;
	}
	va_end(arglist);
	return (1);
}
