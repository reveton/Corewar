/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:58:44 by afomenko          #+#    #+#             */
/*   Updated: 2017/12/13 12:58:45 by afomenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if ((s1 && !s2) || (!s1 && s2))
		return (0);
	if (!s1 && !s2)
		return (1);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}
