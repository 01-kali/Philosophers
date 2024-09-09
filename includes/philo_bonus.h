/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:55 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/28 16:39:31 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	long long	start;
	int			died;
	pid_t		*pids;
	sem_t		*death;
	sem_t		*forks;
}				t_data;

typedef struct s_philo
{
	int			i;
	pid_t		pid;
	int			number_of_meals_eaten;
	long long	last_meal;
	t_data		*data;
}				t_philo;

void			clean(t_data *data, t_philo *philosophers);

void			post_forks(t_data *data);
int				take_forks(t_philo *philosopher, t_data *data);
int				eating(t_philo *philosopher, t_data *data);
void			philo(t_philo *philosopher, t_data *data);

int				check_death(t_philo *philosopher, t_data *data);
int			set_data2(t_philo **philosophers, t_data *data, int argc,
					char **argv);
int			set_data(t_philo **philosophers, t_data *data, int argc,
					char **argv);

long long		get_time(void);
void			ft_usleep(long long time_to_sleep);
int				ft_atoi2(const char *str);
int				ft_atoi(const char *str);

#endif
