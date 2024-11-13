/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:56 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:19:37 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	philosopher->last_meal = get_time();
	printf("%lld %d is eating\n", get_time() - philosopher->data->start,
		philosopher->i + 1);
	ft_usleep(philosopher->data->time_to_eat, philosopher);
	unlock_forks(philosopher);
	philosopher->number_of_meals_eaten++;
	return (0);
}

int	check_one_philo(t_data *data, t_philo *philosopher)
{
	if (data->number_of_philo == 1)
	{
		pthread_mutex_lock(philosopher->l_fork);
		printf("%lld 1 has taken a fork\n", get_time() - data->start);
		ft_usleep(data->time_to_die, philosopher);
		pthread_mutex_unlock(philosopher->l_fork);
		printf("%lld 1 died\n", get_time() - data->start);
		return (1);
	}
	return (0);
}

int	zzz(t_data *data, t_philo *philosopher)
{
	if (!check_death(philosopher))
		printf("%lld %d is sleeping\n", get_time() - data->start, philosopher->i
			+ 1);
	else
		return (1);
	ft_usleep(data->time_to_sleep, philosopher);
	if (!check_death(philosopher))
		printf("%lld %d is thinking\n", get_time() - data->start, philosopher->i
			+ 1);
	else
		return (1);
	return (0);
}

void	*philo(void *arg)
{
	t_philo	*philosopher;
	t_data	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->data;
	if (check_one_philo(data, philosopher))
		return (NULL);
	while (1)
	{
		if (data->number_of_meals != -1
			&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		if (eating(philosopher))
			break ;
		if (data->number_of_meals != -1
			&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		if (zzz(data, philosopher))
			break ;
	}
	return (NULL);
}
