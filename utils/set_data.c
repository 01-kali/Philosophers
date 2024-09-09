/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:37:33 by zelkalai          #+#    #+#             */
/*   Updated: 2024/09/09 14:22:07 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_death(t_philo *philosopher)
{
	t_data	*data;

	data = philosopher->data;
	pthread_mutex_lock(&data->death);
	if (data->died == 1)
	{
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	if (get_time() - philosopher->last_meal > data->time_to_die)
	{
		printf("%lld %d died\n", get_time() - data->start, philosopher->i + 1);
		data->died = 1;
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	pthread_mutex_unlock(&data->death);
	return (0);
}

int	set_data2(t_philo **philosophers, t_data *data, int argc, char **argv)
{
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	data->start = get_time();
	data->died = 0;
	pthread_mutex_init(&data->death, NULL);
	(void)philosophers;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philo);
	if (!data->forks)
	{
		pthread_mutex_destroy(&(*data).death);
		return (1);
	}
	return (0);
}

int	set_data1(t_philo **philosophers, t_data *data, int argc, char **argv)
{
	int	i;

	if (set_data2(philosophers, data, argc, argv))
		return (1);
	*philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philosophers)
		return (pthread_mutex_destroy(&(*data).death), free((*data).forks), 1);
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->number_of_philo)
	{
		(*philosophers)[i].i = i;
		(*philosophers)[i].l_fork = &data->forks[i];
		(*philosophers)[i].r_fork = &data->forks[(\
				i + 1) % data->number_of_philo];
		(*philosophers)[i].number_of_meals_eaten = 0;
		(*philosophers)[i].last_meal = get_time();
		(*philosophers)[i].data = data;
	}
	return (0);
}
