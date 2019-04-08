/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:12:49 by tferrieu          #+#    #+#             */
/*   Updated: 2019/04/08 20:40:40 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*check_exception_0(char *str, int *tab)
{
	if (str[0] == '0')
	{
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
	char *str;

	if (!(str = ft_itobase_ll((unsigned long long int)va_arg(arglist, void *),
					"0123456789abcdef")))
		return (NULL);
	if (!(str = check_exception_0(str, tab)))
		return (NULL);
	len[0] = ft_strlen(str);
	len[1] = biggest_int(3, len[0] + 2, tab[0], tab[1] + 2);
	len[2] = 0;
	if (tab[1] > len[0])
		len[2] = tab[1] - len[0];
	return (str);
}

char		*convert_ptr(va_list arglist, t_printable *args, int *tab)
{
	char	*str;
	char	*arg;
	int		len[3];

	if (!(arg = gather_arg(arglist, tab, len)))
		return (NULL);
	if (!(str = ft_strmake(' ', len[1])))
		return (NULL);
	if (tab[2] == '-')
		ft_strncpy(str + 2 + len[2], arg, len[0]);
	else
		ft_strncpy(str + len[1] - len[0], arg, len[0]);
	if (tab[2] == '-' || tab[2] == '0')
		ft_strncpy(str, "0x", 2);
	else
		ft_strncpy(str + len[1] - len[0] - len[2] - 2, "0x", 2);
	if (tab[2] == '0')
		ft_strnset(str + 2, '0', len[1] - len[0] - 2);
	if (tab[2] == '-' && tab[1] > 0)
		ft_strnset(str + 2, '0', len[2]);
	else if (tab[1] > 0)
		ft_strnset(str + len[1] - len[0] - len[2], '0', len[2]);
	args->len_str = len[1];
	free(arg);
	return (str);
}
