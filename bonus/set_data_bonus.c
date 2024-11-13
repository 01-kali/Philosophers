/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:17 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 17:14:07 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	check_death(t_philo *philosopher, t_data *data, t_philo *ph)
{
	int	i;

	i = 0;
	if (get_time() - philosopher->last_meal > data->time_to_die)
	{
		if (philosopher->i + 1 > 2)
			ft_usleep(4, NULL, NULL, NULL);
		if (philosopher->i + 1 == 1)
			ft_usleep(2, NULL, NULL, NULL);
		usleep(500 + philosopher->i + 1);
		sem_close(data->take);
		sem_unlink("/take");
		sem_close(data->forks);
		sem_unlink("/forks");
		i = philosopher->i + 1;
		free(ph);
		free(data->pids);
		exit(i);
	}
	return (0);
}

int	clean_philo(t_data *data, int i)
{
	sem_close(data->take);
	sem_unlink("/take");
	sem_close(data->forks);
	sem_unlink("/forks");
	if (i == 1)
		free(data->pids);
	return (1);
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
	sem_unlink("/take");
	data->take = sem_open("/take", O_CREAT, 0644, 1);
	if (data->take == SEM_FAILED)
		exit(1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->number_of_philo);
	if (data->forks == SEM_FAILED)
		exit(1);
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->number_of_philo);
	if (!data->pids)
		return (clean_philo(data, 0));
	*philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
	if (!(*philosophers))
		return (clean_philo(data, 1));
	return (0);
}

int	set_data(t_philo **philosophers, t_data *data, int argc, char **argv)
{
	int	i;

	if (set_data2(philosophers, data, argc, argv))
		return (1);
	i = -1;
	data->start = get_time();
	while (++i < data->number_of_philo)
	{
		(*philosophers)[i].i = i;
		(*philosophers)[i].number_of_meals_eaten = 0;
		(*philosophers)[i].last_meal = get_time();
		(*philosophers)[i].data = data;
		(*philosophers)[i].pid = fork();
		if ((*philosophers)[i].pid == 0)
		{
			philo(&(*philosophers)[i], data, *philosophers);
			clean_philo(data, 1);
			free(*philosophers);
			exit(0);
		}
		else if ((*philosophers)[i].pid < 0)
			exit(1);
		data->pids[i] = (*philosophers)[i].pid;
	}
	return (0);
}
