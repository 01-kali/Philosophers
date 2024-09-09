/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:17 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/28 16:38:19 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	check_death(t_philo *philosopher, t_data *data)
{
	sem_wait(data->death);
	if (get_time() - philosopher->last_meal > data->time_to_die)
	{

		sem_post(data->death);
		usleep(2);
		sem_wait(data->death);
		if (philosopher->i + 1 != 2)
		{
			sem_post(data->death);
			ft_usleep(1);
			sem_wait(data->death);
		}
		printf("%lld %d died\n", get_time() - data->start, philosopher->i + 1);
		sem_post(data->death);
		exit(1);
	}
	sem_post(data->death);
	return (0);
}

int clean_philo(t_data *data, int i)
{
  sem_close(data->death);
	sem_close(data->forks);
	sem_unlink("/death");
	sem_unlink("/forks");
  if(i == 1)
    free(data->pids);
  return(1);
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
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->number_of_philo);
	if (data->forks == SEM_FAILED || data->death == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(1);
	}
  data->pids = (pid_t *)malloc(sizeof(pid_t) * data->number_of_philo);
	if(!data->pids)
    return(clean_philo(data, 0)); 
	*philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
  if(!(*philosophers))
    return(clean_philo(data, 1));
  return(0);
}

int	set_data(t_philo **philosophers, t_data *data, int argc, char **argv)
{
	int	i;

	if(set_data2(philosophers, data, argc, argv))
	  return(1);
  i = -1;
	while (++i < data->number_of_philo)
	{
		(*philosophers)[i].i = i;
		(*philosophers)[i].number_of_meals_eaten = 0;
		(*philosophers)[i].last_meal = get_time();
		(*philosophers)[i].data = data;
		(*philosophers)[i].pid = fork();
		if ((*philosophers)[i].pid == 0)
		{
			philo(&(*philosophers)[i], data);
			exit(0);
		}
		else if ((*philosophers)[i].pid > 0)
			data->pids[i] = (*philosophers)[i].pid;
		else
			exit(1);
	}
  return(0);
}
