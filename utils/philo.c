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

long long get_time()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void set_data(t_philo **philosophers ,t_data *data, int argc, char **argv)
{
  int i;

  data->number_of_philo = ft_atoi(argv[1]);
  data->time_to_die = ft_atoi(argv[2]);
  data->time_to_eat = ft_atoi(argv[3]);
  data->time_to_sleep = ft_atoi(argv[4]);
  if(argc == 6)
    data->number_of_meals = ft_atoi(argv[5]);
  else
    data->number_of_meals = -1;
  data->start = get_time();
  data->died = 0;
  data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *\
                                          data->number_of_philo);
  *philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
  if(!data->forks || !philosophers)
    return;
  i = -1;
  while(++i < data->number_of_philo)
    pthread_mutex_init(&data->forks[i],NULL);
  i = -1;
  while(++i < data->number_of_philo)
  {
    (*philosophers)[i].i = i;
    (*philosophers)[i].l_fork = &data->forks[i];
    (*philosophers)[i].r_fork = &data->forks\
      [(i + 1) % data->number_of_philo];
    (*philosophers)[i].number_of_meals_eaten = 0;
    (*philosophers)[i].last_meal = get_time();
    (*philosophers)[i].data = data;
  }
}

void take_forks(t_philo *philosopher)
{
  pthread_mutex_lock(philosopher->l_fork);
  printf("%lld %d has taken a fork\n",get_time() - philosopher->data->start,\
         philosopher->i + 1);
  pthread_mutex_lock(philosopher->r_fork);
  printf("%lld %d has taken a fork\n",get_time() - philosopher->data->start,\
         philosopher->i + 1);
}

void unlock_forks(t_philo *philosopher)
{
  pthread_mutex_unlock(philosopher->l_fork);
  pthread_mutex_unlock(philosopher->r_fork);
}

void eating(t_philo *philosopher)
{
  take_forks(philosopher);
  printf("%lld %d is eating\n",get_time() - philosopher->data->start,\
         philosopher->i + 1);
  usleep(philosopher->data->time_to_eat * 1000);
  philosopher->last_meal = get_time();
  philosopher->number_of_meals_eaten++;
  unlock_forks(philosopher);
}

void *philo(void *arg)
{
  t_philo *philosopher = (t_philo *)arg;
  t_data *data = philosopher->data;
  while(!data->died)
  {
    if(get_time() - philosopher->last_meal > data->time_to_die)
    {
      printf("%lld %d died\n", get_time() - data->start, philosopher->i + 1);
      data->died = 1;
      return(NULL);
    }
    if(data->number_of_meals != -1)
    {
      if(philosopher->number_of_meals_eaten >= data->number_of_meals)
        exit(1);;
    }
    printf("%lld %d is thinking\n",get_time() -\
           data->start,philosopher->i + 1);
    eating(philosopher);
    printf("%lld %d is sleeping\n",get_time() -\
           data->start,philosopher->i + 1);
    usleep(data->time_to_sleep * 1000);
  }
  return(NULL);
}

void create_philo(t_data *data, t_philo *philosophers)
{
  int i;

  i = -1;
  while(++i < data->number_of_philo)
    pthread_create(&philosophers[i].philosopher, NULL, philo, &philosophers[i]);
  i = -1;
  while(++i < data->number_of_philo)
    pthread_join(philosophers[i].philosopher, NULL);
}

int main(int argc, char **argv)
{
  t_data data;
  t_philo *philosophers;
  int i;

  philosophers = NULL;
  if(argc < 5 || argc > 6)
  {
    printf("Error.\n");
    return(1);
  }
  set_data(&philosophers ,&data, argc, argv);
  create_philo(&data, philosophers);
  i = -1;
  while(++i < data.number_of_philo)
    pthread_mutex_destroy(&data.forks[i]);
  free(data.forks);
  free(philosophers);
}
