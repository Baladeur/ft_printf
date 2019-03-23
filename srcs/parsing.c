/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:52:34 by tferrieu          #+#    #+#             */
/*   Updated: 2019/03/23 19:09:36 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	init_printable(const char *restrict format, int *len,
				va_list arglist, t_printable *args)
{
	if (!(args = (t_printable*)malloc(sizeof(t_printable))))
		return (0);
	args->next = NULL;
	if (!(args->str = ))
		return (0);
	len += args->len_flag;
	return (1);
}

static int	add_printable(const char *restrict format, int *len,
				va_list arglist, t_printable *args)
{
	t_printable *pos;

	pos = args;
	while (pos->next)
		pos = pos->next;
	if (!(pos->next = (t_printable*)malloc(sizeof(t_printable))))
		return (0);
	pos = pos->next;
	pos->next = NULL;
	if (!(pos->str = ))
		return (0);
	*len += pos->len_flag;
	return (1);
}

t_printable	*parse(const char *restrict format, va_list arglist, int *len)
{
	t_printable *args;

	args = NULL;
	while (format[*len])
	{
		if (format[*len] == '%' && args == NULL)
		{
			if (!(init_printable(format, len, arglist, args)))
				return (NULL);
		}
		else if (format[*len] == '%')
		{
			if (!(add_printable(format, len, arglist, args)))
				return (NULL);
		}
		else
			*len += 1;
	}
	va_end(
	return (args);
}
