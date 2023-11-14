/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:13:59 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/14 17:12:23 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief 		Checks the length aof a string
/// @param s	The string to check
/// @return		The length of the string
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/// @brief 		Converts a string to a long long Number
/// @param nptr	The string to convert
/// @return		The converted Number
long long	ft_long_atoi(const char *nptr)
{
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (ft_strlen(nptr) > 10)
		return (2147483648);
	while ((*nptr >= 48 && *nptr <= 57) && *nptr)
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sign);
}

/// @brief 		Padds a string with zeros
/// @param s	The begining address to pad
/// @param n	The number of bytes to zero pad
/// @return		Nothing
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

/// @brief		Finds the lowest of two long long Numbers
/// @param a	Number to compare
/// @param b	Number to compare
/// @return		The smallest Number
long long	ft_min(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}
