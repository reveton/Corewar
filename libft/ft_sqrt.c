/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afomenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:57:23 by afomenko          #+#    #+#             */
/*   Updated: 2017/12/13 12:57:24 by afomenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int i;
	int sqrt;

	i = 0;
	sqrt = 1;
	while (sqrt < nb)
	{
		i++;
		sqrt = i * i;
	}
	if (nb % sqrt == 0)
		return (i);
	return (0);
}