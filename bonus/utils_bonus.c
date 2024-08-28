/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:26 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/28 16:38:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
		usleep(time_to_sleep / 10);
}

int	ft_atoi2(const char *str)
{
	if (*str && *str != ' ' && (*str < '0' || *str > '9'))
		return (-1);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
			|| *str == '\r' || *str == '\f'))
		str++;
	if (*str != '\0')
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	s;

	r = 0;
	s = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '\0')
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (ft_atoi2(str) == -1)
		return (-1);
	return ((int)r * s);
}
