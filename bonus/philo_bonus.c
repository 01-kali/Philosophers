/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:01 by zelkalai          #+#    #+#             */
/*   Updated: 2024/09/09 14:10:07 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	post_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}

int	take_forks(t_philo *philosopher, t_data *data, t_philo *ph)
{
	if ((philosopher->i + 1) % 2 == 1)
		usleep(600);
	sem_wait(data->forks);
	if (!check_death(philosopher, data, ph))
		printf("%lld %d has taken a fork \n", get_time() - data->start,
			philosopher->i + 1);
	if ((philosopher->i + 1) % 2 == 1)
		usleep(50);
	sem_wait(data->take);
	sem_wait(data->forks);
	sem_post(data->take);
	if (!check_death(philosopher, data, ph))
		printf("%lld %d has taken a fork\n", get_time() - data->start,
			philosopher->i + 1);
	return (0);
}

int	eating(t_philo *philosopher, t_data *data, t_philo *ph)
{
	take_forks(philosopher, data, ph);
	philosopher->last_meal = get_time();
	printf("%lld %d is eating\n", get_time() - data->start, philosopher->i + 1);
	ft_usleep(data->time_to_eat, philosopher, data, ph);
	post_forks(data);
	philosopher->number_of_meals_eaten++;
	return (0);
}

int	check_one_philo(t_data *data, t_philo *philosopher)
{
	if (data->number_of_philo == 1)
	{
    if (data->number_of_meals != -1
      && philosopher->number_of_meals_eaten >= data->number_of_meals)
      return (1);
		printf("%lld 1 has taken a fork\n", get_time() - data->start);
		ft_usleep(data->time_to_die, NULL, NULL, NULL);
		printf("%lld 1 died\n", get_time() - data->start);
		return (1);
	}
	return (0);
}

void	philo(t_philo *philosopher, t_data *data, t_philo *ph)
{
	if (check_one_philo(data, philosopher))
		return ;
	while (1)
	{
		if (data->number_of_meals != -1
			&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		eating(philosopher, data, ph);
		if (data->number_of_meals != -1
			&& philosopher->number_of_meals_eaten >= data->number_of_meals)
			break ;
		if (!check_death(philosopher, data, ph))
			printf("%lld %d is sleeping\n", get_time() - data->start,
				philosopher->i + 1);
		ft_usleep(data->time_to_sleep, philosopher, data, ph);
		if (!check_death(philosopher, data, ph))
			printf("%lld %d is thinking\n", get_time() - data->start,
				philosopher->i + 1);
	}
}
