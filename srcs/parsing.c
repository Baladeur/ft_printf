/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:52:34 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 15:56:49 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*convert_core(va_list arglist, t_printable *args, char *flags,
		char id)
{
	if (id == 'c' || id == '%')
		return (convert_char(arglist, args, flags, id == 'c' ? 1 : 0));
	else if (ft_strchr("ouxX", id))
		return (convert_unsigned(arglist, args, flags, id));
	else if (id == 'i' || id == 'd')
		return (convert_int(arglist, args, flags));
	else if (id == 's')
		return (convert_str(arglist, args, flags));
	else if (id == 'p')
		return (convert_ptr(arglist, args, flags));
	else
		return (NULL);
}

static char	*identifier(const char *restrict format, va_list arglist,
		t_printable *args)
{
	char	*flags;
	int		l;

	flags = NULL;
	l = 1;
	while (format[l] && ft_strchr("hlL#0-+.123456789 ", format[l]))
		l++;
	if (!format[l] || !(ft_strchr("cspdiouxXf%hlL#0-+.123456789 ", format[l])))
	{
		args->len_flag = l;
		args->len_str = 0;
		return (ft_strnew(0));
	}
	args->len_flag = l + 1;
	if (!(flags = ft_strnew(l - 1)))
		return (NULL);
	flags = ft_strncpy(flags, format + 1, l - 1);
	return (convert_core(arglist, args, flags, format[l]));
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
