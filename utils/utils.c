/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:17:19 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:19:55 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	take_forks2(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->r_fork);
	if (!check_death(philosopher))
		printf("%lld %d has taken a fork\n", get_time()
			- philosopher->data->start, philosopher->i + 1);
	pthread_mutex_lock(philosopher->l_fork);
	if (!check_death(philosopher))
		printf("%lld %d has taken a fork\n", get_time()
			- philosopher->data->start, philosopher->i + 1);
	else
	{
		unlock_forks(philosopher);
		return (1);
	}
	return (0);
}

int	take_forks1(t_philo *philosopher)
{
	usleep(100);
	pthread_mutex_lock(philosopher->l_fork);
	if (!check_death(philosopher))
		printf("%lld %d has taken a fork\n", get_time()
			- philosopher->data->start, philosopher->i + 1);
	usleep(50);
	pthread_mutex_lock(philosopher->r_fork);
	if (!check_death(philosopher))
		printf("%lld %d has taken a fork\n", get_time()
			- philosopher->data->start, philosopher->i + 1);
	else
	{
		unlock_forks(philosopher);
		return (1);
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep, t_philo *philosopher)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
	{
		if (philosopher != NULL && check_death(philosopher))
			return ;
		usleep(time_to_sleep / 1000);
	}
}

void	unlock_forks(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->r_fork);
	pthread_mutex_unlock(philosopher->l_fork);
}
