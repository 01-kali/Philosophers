/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:27:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/06 17:27:16 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
# include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

typedef struct s_philo
{
  int i;
  pthread_t philosopher;
  pthread_mutex_t *l_fork;
  pthread_mutex_t *r_fork;
  int number_of_meals_eaten;
} t_philo;

typedef struct s_data
{
  int number_of_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_meals;
  pthread_mutex_t *forks;
  t_philo *philosophers;
} t_data;

#endif
