/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:56 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/23 05:45:40 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	take_forks2(t_philo *philosopher)
{
	if (check_death(philosopher))
		return (1);
	pthread_mutex_lock(philosopher->r_fork);
	if (check_death(philosopher))
	{
		pthread_mutex_unlock(philosopher->r_fork);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
			get_time() - \
			philosopher->data->start, \
			philosopher->i + 1);
	pthread_mutex_lock(philosopher->l_fork);
	if (check_death(philosopher))
	{
		unlock_forks(philosopher);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
			get_time() - \
			philosopher->data->start, \
			philosopher->i + 1);
	return (0);
}

int	take_forks1(t_philo *philosopher)
{
	usleep(500);
	if (check_death(philosopher))
		return (1);
	pthread_mutex_lock(philosopher->l_fork);
	if (check_death(philosopher))
	{
		pthread_mutex_unlock(philosopher->l_fork);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
			get_time() - philosopher->data->start, \
			philosopher->i + 1);
	pthread_mutex_lock(philosopher->r_fork);
	if (check_death(philosopher))
	{
		unlock_forks(philosopher);
		return (1);
	}
	printf("%lld %d has taken a fork\n", \
			get_time() - philosopher->data->start, \
			philosopher->i + 1);
	return (0);
}

int	take_forks0(t_philo *philosopher)
{
	if ((philosopher->i + 1) % 2 == 1)
	{
		if (take_forks1(philosopher))
			return (1);
	}
	else
	{
		if (take_forks2(philosopher))
			return (1);
	}
	return (0);
}

int	eating(t_philo *philosopher)
{
	if (take_forks0(philosopher))
		return (1);
	if (check_death(philosopher))
	{
		unlock_forks(philosopher);
		return (1);
	}
	philosopher->last_meal = get_time();
	printf("%lld %d is eating\n", get_time() - philosopher->data->start, \
			philosopher->i + 1);
	ft_usleep(philosopher->data->time_to_eat);
	unlock_forks(philosopher);
	philosopher->number_of_meals_eaten++;
	if (check_death(philosopher))
		return (1);
	return (0);
}

void	*philo(void *arg)
{
	t_philo	*philosopher;
	t_data	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->data;
	while (1)
	{
		if (eating(philosopher))
			break ;
		if (data->number_of_meals != -1 \
				&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		printf("%lld %d is sleeping\n", \
				get_time() - data->start, \
				philosopher->i + 1);
		ft_usleep(data->time_to_sleep);
		if (check_death(philosopher))
			break ;
		printf("%lld %d is thinking\n", \
				get_time() - data->start, \
				philosopher->i + 1);
	}
	return (NULL);
}
