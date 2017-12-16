/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_octal_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:54:30 by afomenko          #+#    #+#             */
/*   Updated: 2017/12/13 12:54:31 by afomenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_octal_str(t_saver *saver, va_list arg)
{
	char				*str;
	char				*final;
	unsigned long long	unsigned_nbr;

	unsigned_nbr = get_unsigned_number_arg(saver, arg);
	str = ft_utoa_base(unsigned_nbr, 8);
	if (saver->hash == '#' && str[0] != '0')
	{
		final = ft_strjoin("0", str);
		free(str);
	}
	else
		final = str;
	if (unsigned_nbr == 0 && saver->precision == 0 && saver->hash != '#')
	{
		free(final);
		final = ft_strdup("");
	}
	final = add_precision(saver, final);
	final = add_min_width(saver, final);
	return (final);
}
