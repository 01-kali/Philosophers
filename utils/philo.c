/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:56 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:58 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void set_data(t_data *data, int argc, char **argv)
{
  int i;

  i = -1;
  data->number_of_philo = ft_atoi(argv[1]);
  data->time_to_die = ft_atoi(argv[2]);
  data->time_to_eat = ft_atoi(argv[3]);
  data->time_to_sleep = ft_atoi(argv[4]);
  if(argc == 6)
    data->number_of_meals = ft_atoi(argv[5]);
  else
    data->number_of_meals = -1;
  printf("%d %d %d %d %d\n",data->number_of_philo,data->time_to_die,data->time_to_eat,data->time_to_sleep,data->number_of_meals);
  data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
  data->philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
  if(!data->forks || !data->philosophers)
    exit(1);
  while(++i < data->number_of_philo)
  {
    data->philosophers[i].i = i;
    data->philosophers[i].l_fork = &data->forks[i];
    data->philosophers[i].r_fork = &data->forks\
      [(i + 1) % data->number_of_philo];
    data->philosophers[i].number_of_meals_eaten = 0;
  }
}

void *philo(void *arg)
{
  t_philo *philosofer = (t_philo *)arg;

  while(1)
  {

  }
}

void create_philo(t_data *data)
{
  int i;

  i = -1;
  while(++i < data->number_of_philo)
    pthread_create(&data->philosophers[i].philosopher, NULL, philo, &data->philosophers[i]);
  i = -1;
  while(++i < data->number_of_philo)
    pthread_join(data->philosophers[i].philosopher, NULL);
}

int main(int argc, char **argv)
{
  t_data data;
  
  if(argc < 5 || argc > 6)
  {
    printf("Error.\n");
    return(1);
  }
  set_data(&data, argc, argv);
  create_philo(&data);
}
