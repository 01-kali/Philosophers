/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:27:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/23 05:42:34 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long long		start;
	int				died;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				i;
	pthread_t		philosopher;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				number_of_meals_eaten;
	long long		last_meal;
	t_data			*data;
}					t_philo;

void				dest(t_data *data, t_philo *philosophers);
int					check_arg(int argc, char **argv);

int					take_forks2(t_philo *philosopher);
int					take_forks1(t_philo *philosopher);
int					take_forks0(t_philo *philosopher);
int					eating(t_philo *philosopher);
void				*philo(void *arg);

int					check_death(t_philo *philosopher);
void				set_data2(t_philo **philosophers, t_data *data, int argc,
						char **argv);
void				set_data1(t_philo **philosophers, t_data *data, int argc,
						char **argv);

void				create_philo(t_data *data, t_philo *philosophers);

long long			get_time(void);
void				ft_usleep(long long time_to_sleep);
void				unlock_forks(t_philo *philosopher);
int					ft_atoi2(const char *str);
int					ft_atoi(const char *str);

#endif
