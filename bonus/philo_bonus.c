/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:01 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/28 16:38:02 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	post_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}

int	take_forks(t_philo *philosopher, t_data *data)
{
	if ((philosopher->i + 1) % 2 == 1)
		usleep(600);
	sem_wait(data->forks);
	if (check_death(philosopher, data))
	{
		sem_post(data->forks);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_time() - data->start, \
			philosopher->i + 1);
	sem_wait(data->forks);
	if (check_death(philosopher, data))
	{
		post_forks(data);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_time() - data->start, \
			philosopher->i + 1);
	return (0);
}

int	eating(t_philo *philosopher, t_data *data)
{
	if (take_forks(philosopher, data))
		return (1);
	if (check_death(philosopher, data))
	{
		post_forks(data);
		return (1);
	}
	philosopher->last_meal = get_time();
	printf("%lld %d is eating\n", get_time() - data->start, philosopher->i + 1);
	ft_usleep(data->time_to_eat);
	post_forks(data);
	philosopher->number_of_meals_eaten++;
	if (check_death(philosopher, data))
		return (1);
	return (0);
}

void	philo(t_philo *philosopher, t_data *data)
{
	if (data->number_of_philo == 1)
	{
		printf("%lld 1 has taken a fork\n", get_time() - data->start);
		ft_usleep(data->time_to_die);
		printf("%lld 1 died\n", get_time() - data->start);
		return ;
	}
	while (1)
	{
		if (eating(philosopher, data))
			break ;
		if (data->number_of_meals != -1
			&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		printf("%lld %d is sleeping\n", get_time() - data->start, \
				philosopher->i + 1);
		ft_usleep(data->time_to_sleep);
		if (check_death(philosopher, data))
			break ;
		printf("%lld %d is thinking\n", get_time() - data->start, \
				philosopher->i + 1);
		usleep(200);
	}
}
