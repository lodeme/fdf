/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:22:04 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/25 20:18:51 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	find_xindex(char c)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if ("0123456789ABCDEF"[i] == c)
			return (i);
		if ("0123456789abcdef"[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_xtoi(const char *nptr)
{
	long long	nbr;

	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '0' && *(nptr + 1) == 'x')
		nptr += 2;
	while ((*nptr >= '0' && *nptr <= '9') || (*nptr >= 'A' && *nptr <= 'F') || \
												(*nptr >= 'a' && *nptr <= 'f'))
		nbr = nbr * 16 + find_xindex(*nptr++);
	if (nbr > UINT_MAX)
		return (0);
	nbr = (nbr << 8) | 0xFF;
	return (nbr);
}
