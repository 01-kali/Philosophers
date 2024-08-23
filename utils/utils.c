/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:17:19 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/23 05:17:21 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long get_time()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
		usleep(time_to_sleep / 10);
}

void unlock_forks(t_philo *philosopher)
{
  pthread_mutex_unlock(philosopher->l_fork);
  pthread_mutex_unlock(philosopher->r_fork);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	s;

	r = 0;
	s = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	return ((int)r * s);
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
