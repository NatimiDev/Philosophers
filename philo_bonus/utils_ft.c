/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:32:10 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/14 20:52:45 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
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

#include <stdlib.h>
#include <string.h>

void	get_sem_name(char *dest, int id)
{
	const char	*prefix = "/sem_meal_time_";
	int			i = 0;
	int			j = 0;
	char		id_str[12];

	while (prefix[i])
	{
		dest[i] = prefix[i];
		i++;
	}
	if (id == 0)
		id_str[j++] = '0';
	else
	{
		int	tmp = id;
		char	tmp_str[12];
		int		k = 0;

		while (tmp > 0)
		{
			tmp_str[k++] = '0' + (tmp % 10);
			tmp /= 10;
		}
		while (k-- > 0)
			id_str[j++] = tmp_str[k];
	}
	id_str[j] = '\0';
	j = 0;
	while (id_str[j])
		dest[i++] = id_str[j++];
	dest[i] = '\0';
}
