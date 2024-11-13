/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:26 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:27:25 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep, t_philo *philosopher, t_data *data,
		t_philo *ph)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
	{
		if (philosopher != NULL && data != NULL && check_death(philosopher,
				data, ph))
			return ;
		usleep(time_to_sleep / 1000);
	}
}
