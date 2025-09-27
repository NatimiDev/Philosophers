/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:32:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/26 21:47:18 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_is_natural_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	number;

	sign = 1;
	number = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str ++;
	}
	if (*str == '+')
		str ++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		if (number > INT_MAX)
			return (INT_MAX);
		str++;
	}
	return (sign * number);
}

void	ft_perror(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(STDERR_FILENO, s, 1);
		s++;
	}
	write(STDERR_FILENO, "\n", 1);
}

void	get_sem_name(char *dest, int id)
{
	const char	*prefix;
	int			i;
	int			j;
	char		id_str[12];

	prefix = "/sem_meal_time_";
	i = 0;
	while (prefix[i])
	{
		dest[i] = prefix[i];
		i++;
	}
	j = 0;
	while (id > 0)
	{
		id_str[j++] = '0' + (id % 10);
		id /= 10;
	}
	while (j-- > 0)
		dest[i++] = id_str[j];
	dest[i] = '\0';
}
